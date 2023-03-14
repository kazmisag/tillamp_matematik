// Libraries to be included
#include <Arduion.h>
#include <iostream>
#include <math.h>

/*
Home light automation system: The system is developed to save electric energy and to create a smart
home with an automatic light management system.

Lights operated and controlled with following features:

Following functions might be included and implemented within the system as module or sub-module
*/


// Following module can be used to control light brightness of LED in forever loop or otherwise
#define INTERVAL 50
#define VOLT_MIN 0.0f
#define VOLT_MAX 3.3f
#define DAC_RESOLUTION 12
#define VOLT_RESOLUTION ((3.3) / (1 << DAC_RESOLUTION))
void brightness(void)
{
    static float fadingStep = 0.15f;
    static float voltage = VOLT_MAX;

    // setup DAC resolution in setup()
    analogWriteResolution(DAC_RESOLUTION);

    // write to DAC1 pin
    analogWriteDAC1((int)(voltage / VOLT_RESOLUTION));

    // increase voltage to increase brightness
    voltage += fadingStep;

    // Decerease brightness when maximum voltage is reached
    if (voltage <= VOLT_MIN || voltage >= VOLT_MAX)
    {
        voltage -= fadingStep; // reset voltage to Minimum
        fadingStep = -fadingStep;
    }

    delay(INTERVAL); // use arduino for delay
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Following Mathematical functions could be translated in C++ code to implement various functions or modules//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Stein  Heart Equation for temperature using Thermister sensor in Arduino libarary
//(voltage=5v, Temperature range = -55°C to 125°C [-67°F to 257°F])
double SHE_temperature(int ADC_res)
{
    double temperature = 0.0;
    temperature = log(((10240000 / ADC_res) - 10000)); //
    temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp)) * Temp);
    return temperature - 273.15; // return temperature in Celcius
}

// Implementation code to calculate TMP36 Analog Temperature sensor (voltage = 3.3v)
#define TMP_ANA_PIN A14 // use analog pin from arudion board
#define ADC_RESOLUTION (10)
#define VOLTAGE_OFFSET (500)
#define MILLIVOLTS_PER_CELCIUS (10)
#define VOLTAGE_RESOLUTION ((3.3f) * 1000 / (1 << ADC_RESOLUTION))

float read_temperature(void)
{
    int sensorReading = analogRead(TMP_ANA_PIN); // analog reading of the sensor pin

    float voltage = sensorReading * VOLTAGE_RESOLUTION; // convert into voltage

    // convert into temperature using formula  (voltage - offset) / milli volts per celcius
    float sensorTemperature = (voltage - VOLTAGE_OFFSET) / MILLIVOLTS_PER_CELCIUS;
    return sensorTemperature;
}

// Calculate Mean of room temperature to use it for turning on/off the heating

double mean_temperature(float temp[], int total_readings)
{
    // check room temperature after every 10 seconds or so for 3 times to calculate mean
    for (int temp_check = 0; temp_check < total_readings; temp_check++)
    {
        temp += read_temperature();
        delay(10000); // use arduion delay function
    }
    return temp / total_readings;
}

// Calculate Median of room temperature
double median_temperature(float temp[], int total_readings)
{
    bool is_even = false;
    for (int i = 0; i < total_readings - 1; i++)
    {

        for (int j = i; j < total_readings; j++)
        {
            if (temp[j] < temp[j + 1])
            {
                float t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }
    is_even = (total_readings / 2 == 0) ? return temp[(total_readings / 2)] : return temp[(total_readings / 2) + 1];
}

/// Newton's 2nd Law implementation

double newtons_law2(double mass, double acc)
{
    double force = mass * acc; // return force
    return force;
}

// Universal gravitational pull/force equation Implementation
double newtons_law3(double m1, double m2, double r)
{
    const double G = 6.6742E-11;
    double force = G * ((m1 * m2 / r*r));

    return force;
}