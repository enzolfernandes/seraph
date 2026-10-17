# Seraph — minhas contribuições ao robô de combate da TERA

Contribuí com firmware para o Seraph, robô de combate Hobbyweight (12 lb, aproximadamente 5,44 kg) da equipe TERA, controlado com ESP32 e controle PS4 por Bluetooth. Este é meu fork de [roboticatera/Seraph](https://github.com/roboticatera/Seraph); o projeto e seu histórico são coletivos.

## Minha contribuição documentada

| Alteração | Evidência |
| --- | --- |
| Fator de correção no comando de locomoção e correção da condição da zona linear | [c363855 — 13/07/2023](https://github.com/enzolfernandes/seraph/commit/c3638554e332f0e63c0a10924f186c28e7bc60a2) |
| Comando de parada de um dos motores nas curvas | [b98e1de — 18/07/2023](https://github.com/enzolfernandes/seraph/commit/b98e1de2d4b6907e382dde600b827f01603bc263) |

Esses commits mostram alterações no firmware; não quantificam ganho de desempenho ou estabilidade mecânica.

## Arquitetura

| Arquivo/pasta | Papel |
| --- | --- |
| [src/main.cpp](src/main.cpp) | Inicialização, timers PWM e loop controlado |
| [include/joystick.cpp](include/joystick.cpp) | Conexão e configuração do controle |
| [include/controlled.cpp](include/controlled.cpp) | Locomoção, comando da arma e parada na desconexão |
| [include/motors.cpp](include/motors.cpp) | Saídas e parâmetros dos ESCs |
| [lib](lib) | ESP32Servo e PS4-esp32, dependências de terceiros |
| [test/test_main.cpp](test/test_main.cpp) | Rotinas Unity dependentes de controle e motores |

## Preparar a compilação

O [platformio.ini](platformio.ini) declara ESP32 DOIT DevKit V1, `espressif32` e framework Arduino. Com PlatformIO disponível:

```shell
git clone https://github.com/enzolfernandes/seraph.git
cd seraph
pio run -e esp32doit-devkit-v1
```

A plataforma não tem versão fixada. Confira a compatibilidade das bibliotecas e as configurações de pinagem, pulsos e ESCs para reproduzir o ambiente histórico. A instrução acima não representa uma compilação executada nesta revisão.

## Estado dos testes

Há código de teste que envia comandos aos motores e à arma, além de verificações de conexão. Algumas asserções são apenas `TEST_ASSERT(true)` e não demonstram o resultado físico. A revisão atual inspecionou código e histórico, sem acionar hardware ou produzir um novo relatório de testes.

## Origem e autoria

A documentação original relaciona o controle à [CombatIO V3](https://github.com/roboticatera/CombatIO). Mantenho a atribuição da equipe e das bibliotecas externas; não há licença geral declarada na raiz inspecionada.

*Apresentação revisada em 17/10/2026; implementação preservada.*
