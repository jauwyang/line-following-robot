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

