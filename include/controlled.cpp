constexpr const short minimumTriggerValue = 0;
constexpr const short maximumTriggerValue = 255;

constexpr const short minimumStickValue = -127;
constexpr const short maximumStickValue = 127;
constexpr const short deadZone = 15;
constexpr const short linearZone = deadZone + 10;

short x = 0, y = 0, mapXValue = 0, mapYValue = 0;

void controlledLoop()
{
        if (PS4.isConnected())
        {
                // Arma
                weapon.write(constrain(map(PS4.R2Value(), minimumTriggerValue, maximumTriggerValue, stopped, forward), stopped, forward));
#ifdef _DEBUG_
                Serial.println("----------");
                Serial.print("Arma: ");
                Serial.println(constrain(map(PS4.R2Value(), minimumTriggerValue, maximumTriggerValue, stopped, forward), stopped, forward));
#endif

                // Locomoção
                x = PS4.LStickX();
                mapXValue = map(x, minimumStickValue, maximumStickValue, stopped, forward);

                y = PS4.LStickY();
                mapYValue = map(y, minimumStickValue, maximumStickValue, stopped, forward);

#ifdef _DEBUG_
                Serial.print("Eixo X do Analogico: ");
                Serial.println(x);
                Serial.print("Eixo X Re-mapeado: ");
                Serial.println(mapXValue);

                Serial.print("Eixo Y do Analogico: ");
                Serial.println(y);
                Serial.print("Eixo Y Re-mapeado: ");
                Serial.println(mapYValue);
#endif

                if ((pow(x, 2) + pow(y, 2)) <= pow(deadZone, 2)) // Interior do Círculo de Zona Morta
                {
                        leftMotor.write(stopped);
                        rightMotor.write(stopped);
#ifdef _DEBUG_
                        Serial.println("Zona Morta");
#endif
                }
                else if (-linearZone < x < linearZone)
                {
                        leftMotor.write(constrain(mapYValue, stopped, forward));
                        rightMotor.write(constrain(mapYValue, stopped, forward));

#ifdef _DEBUG_
                        Serial.println("Zona de Movimento Linear");
                        Serial.print("Valor enviado aos motores: ");
                        Serial.println(constrain(mapYValue, stopped, forward));
#endif
                }
                else if (x < -linearZone || x > linearZone)
                {
                        leftMotor.write(constrain((mapYValue + mapXValue), stopped, forward));
                        rightMotor.write(constrain((mapYValue - mapXValue), stopped, forward));

#ifdef _DEBUG_
                        Serial.println("Zona de Movimento Curvo");
                        Serial.print("Valor enviado ao motor Esquerdo: ");
                        Serial.println(constrain((mapYValue + mapXValue), stopped, forward));
                        Serial.print("Valor enviado ao motor Direto: ");
                        Serial.println(constrain((mapYValue - mapXValue), stopped, forward));
#endif
                }
        }
        else
        {
                leftMotor.write(stopped);
                rightMotor.write(stopped);
                weapon.write(stopped);
        }
}