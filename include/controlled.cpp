constexpr const short minimumTriggerValue = 0;
constexpr const short maximumTriggerValue = 255;

constexpr const short minimumStickValue = -127;
constexpr const short maximumStickValue = 127;
constexpr const short deadZone = 10;
constexpr const short linearZone = deadZone + 10;

constexpr const short correction = forward * 0.2; // Correção aplicada no motor esquerdo para atingirem rotação semelhante, já que o ESC não é o mesmo

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
                Serial.println(weapon.read());

                Serial.println();
#endif

                // Locomoção
                x = PS4.LStickX();
                mapXValue = map(x, minimumStickValue, maximumStickValue, stopped, forward);

                y = PS4.LStickY();
                mapYValue = map(y, minimumStickValue, maximumStickValue, stopped, forward);

#ifdef _DEBUG_
                Serial.print("Eixo X do Analogico: ");
                Serial.println(x);
                Serial.print("Eixo Y do Analogico: ");
                Serial.println(y);

                Serial.println();

                Serial.print("Eixo X Re-mapeado: ");
                Serial.println(mapXValue);
                Serial.print("Eixo Y Re-mapeado: ");
                Serial.println(mapYValue);

                Serial.println();
#endif

                if ((pow(x, 2) + pow(y, 2)) <= pow(deadZone, 2)) // Interior do Círculo de Zona Morta
                {
                        leftMotor.write(stopped);
                        rightMotor.write(stopped);
#ifdef _DEBUG_
                        Serial.println("Zona Morta");
#endif
                }
                else if (-linearZone < x && x < linearZone)
                {
                        leftMotor.write(constrain(mapYValue, stopped, forward) - correction);
                        rightMotor.write(constrain(mapYValue, stopped, forward));

#ifdef _DEBUG_
                        Serial.println("Zona de Movimento Linear");
                        Serial.print("Valor enviado ao motor Esquerdo: ");
                        Serial.println(leftMotor.read());
                        Serial.print("Valor enviado ao motor Direto: ");
                        Serial.println(rightMotor.read());
#endif
                }
                else if (x <= -linearZone) // Zona Esquerda
                {
                        leftMotor.write(stopped);
                        rightMotor.write(constrain(mapYValue, stopped, forward));

#ifdef _DEBUG_
                        Serial.println("Zona de Movimento Curvilíneo Esquerdo");
                        Serial.print("Valor enviado ao motor Esquerdo: ");
                        Serial.println(leftMotor.read());
                        Serial.print("Valor enviado ao motor Direito: ");
                        Serial.println(rightMotor.read());
#endif
                }
                else if (x >= linearZone) // Zona Direita
                {

                        leftMotor.write(constrain(mapYValue, stopped, forward) - correction);
                        rightMotor.write(stopped);

#ifdef _DEBUG_
                        Serial.println("Zona de Movimento Curvilíneo Direito");
                        Serial.print("Valor enviado ao motor Esquerdo: ");
                        Serial.println(leftMotor.read());
                        Serial.print("Valor enviado ao motor Direito: ");
                        Serial.println(rightMotor.read());
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