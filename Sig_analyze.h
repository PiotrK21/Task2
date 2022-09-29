#ifndef SIG_ANALYZE_H_INCLUDED
#define SIG_ANALYZE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "cjson.h"

/*
    The function calculates the standard deviation and the coefficient of variation until the requirements are met
*/

bool fun_signal_analyze(char* data)
{
    cJSON *element;
    cJSON *json = cJSON_Parse(data);

    int array_size = cJSON_GetArraySize(json);
    int time_min, time_max, first_sample, select_value;

    double coefficient_variation = 0;
    double input_rel_range = 0;
    double sum_n = 0;
    double mean_n = 0;
    double pow_n = 0;
    double sum_pow_n = 0;
    double standard_deviation = 0;
    double input_abs_range = 0;

    bool analyze_result = true;

    printf("\nPlease select [input 0 or 1] :\n\n[0] Absolute value (standard deviation)\n[1] Relative value (coefficient of variation)\n\nof permissible range: ");
    scanf("%d",&select_value);

    if(select_value==0)
    {
        printf("\nPlease input permissible value of standard deviation in the unit of measure: ");
        scanf("%lf",&input_abs_range);
    }
    else if(select_value==1)
    {
        printf("\nPlease input permissible value of coefficient of variation in percent: ");
        scanf("%lf",&input_rel_range);
    }
    else
    {
        printf("\nIncorrect input value\n");
        exit(1);
    }

    printf("\nPlease input maximum allowed time for which the measured signal can be outside of the defined range: ");
    scanf("%d",&time_max);
    printf("\nPlease input minimum allowed time between the events from the point above: ");
    scanf("%d",&time_min);

    for(int i=0, timestamp_max = 0, timestamp_min = time_min; i < array_size; i++)
    {
        element = cJSON_GetArrayItem(json, i);

        sum_n += element->valuedouble;

        mean_n = sum_n/(i+1);

        pow_n = element->valuedouble-mean_n;

        pow_n *= pow_n;

        sum_pow_n+=pow_n;

        standard_deviation = sqrt(sum_pow_n/(i+1));

        coefficient_variation = (standard_deviation/mean_n)*100;

        if(timestamp_max > time_max)
        {
            analyze_result = false;
            printf("\nResult: False \nTimestamp, dependent on sampling time, of the first value out of range: %d\n", i-timestamp_max);
            break;
        }
        else if ((input_abs_range < standard_deviation && select_value == 0) || (input_rel_range < coefficient_variation && select_value == 1))
        {
            if (timestamp_min < time_min && timestamp_min > 0)
            {
                analyze_result = false;
                printf("\nResult: False \nTimestamp of the first value out of range: %d\n", first_sample);
                break;
            }
            else
            {
                timestamp_max++;
                timestamp_min = time_min;
            }
        }
        else if (((input_abs_range >= standard_deviation && select_value == 0) || (input_rel_range >= coefficient_variation && select_value == 1)) && (timestamp_max > 0 || timestamp_min < time_min))
        {
            if (timestamp_min == time_min)
            {
                first_sample = i-timestamp_max;
            }

            timestamp_min--;
            timestamp_max = 0;
        }
        else
        {
            timestamp_max = 0;
        }
    }

    if(analyze_result == true)
    {
        printf("\nResult: True \n");
    }

    return analyze_result;
}

#endif // SIG_ANALYZE_H_INCLUDED
