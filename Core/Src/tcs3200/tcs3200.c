#include "tcs3200/tcs3200.h"

#include <stdio.h>

extern TIM_HandleTypeDef htim3;


void tcs3200_select_filter(tcs3200_t *sensor, const filter_colour_e filter) {
	switch (filter) {
	case FILTER_RED:
		HAL_GPIO_WritePin(sensor->select_ports[S2], sensor->select_pins[S2], GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sensor->select_ports[S3], sensor->select_pins[S3], GPIO_PIN_RESET);
		break;
	case FILTER_GREEN:
		HAL_GPIO_WritePin(sensor->select_ports[S2], sensor->select_pins[S2], GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sensor->select_ports[S3], sensor->select_pins[S3], GPIO_PIN_SET);
		break;
	case FILTER_CLEAR:
		HAL_GPIO_WritePin(sensor->select_ports[S2], sensor->select_pins[S2], GPIO_PIN_SET);
		HAL_GPIO_WritePin(sensor->select_ports[S3], sensor->select_pins[S3], GPIO_PIN_RESET);
		break;
	case FILTER_BLUE:
		HAL_GPIO_WritePin(sensor->select_ports[S2], sensor->select_pins[S2], GPIO_PIN_SET);
		HAL_GPIO_WritePin(sensor->select_ports[S3], sensor->select_pins[S3], GPIO_PIN_SET);
		break;
	default:
		printf("%s\r\n", "Invalid colour filter selected.");
		break;
	}
}

void tcs3200_select_frequency(tcs3200_t *sensor, const frequency_scale_e frequency) {
	switch (frequency) {
	case FREQ_PWDWN:
		HAL_GPIO_WritePin(sensor->select_ports[S0], sensor->select_pins[S0], GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sensor->select_ports[S1], sensor->select_pins[S1], GPIO_PIN_RESET);
		break;
	case FREQ_2_PERCENT:
		HAL_GPIO_WritePin(sensor->select_ports[S0], sensor->select_pins[S0], GPIO_PIN_RESET);
		HAL_GPIO_WritePin(sensor->select_ports[S1], sensor->select_pins[S1], GPIO_PIN_SET);
		break;
	case FREQ_20_PERCENT:
		HAL_GPIO_WritePin(sensor->select_ports[S0], sensor->select_pins[S0], GPIO_PIN_SET);
		HAL_GPIO_WritePin(sensor->select_ports[S1], sensor->select_pins[S1], GPIO_PIN_RESET);
		break;
	case FREQ_100_PERCENT:
		HAL_GPIO_WritePin(sensor->select_ports[S0], sensor->select_pins[S0], GPIO_PIN_SET);
		HAL_GPIO_WritePin(sensor->select_ports[S1], sensor->select_pins[S1], GPIO_PIN_SET);
		break;
	default:
		printf("%s\r\n", "Invalid frequency scale selected.");
		break;
	}
}

void tcs3200_read_colour_callback(tcs3200_irqh_params_t *params, TIM_HandleTypeDef *htim) {
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
		if (!params->start_capture_flag) {
			params->start_val = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			params->start_capture_flag = true;

		} else {
			params->end_val = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			__HAL_TIM_SET_COUNTER(htim, 0);

			params->difference = (params->end_val > params->start_val)
							   ? params->end_val - params->start_val
							   : ((uint32_t) 0xFFFF - params->start_val) + params->end_val;

			params->start_capture_flag = false;
			__HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);
		}
	}
}
