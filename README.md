# Repositorio definitivo para el proyecto.

## Abstract
The use of wheeled mobile robots has been the subject of research for several years along with the study of control algorithms suitable for activities that can become complicated for humans; one of these algorithms is the one that consists of a robot that traces a path when navigating and another that follows said path.
In the present work, a control algorithm is developed for leader-follower tracking, consisting of a mobile robot with Ackerman steering geometry taking the role of leader and a mobile robot with differential steering for the follower. The theory of the mathematical model used in the design of the controller, it’s implementation in software and the construction of the prototype in hardware are included.
For the development of the leader robot, a mid-range microcontroller is used, together with an ultrasonic sensor that detects and measures the distance between all objects that reflect sound and the robot so the later can avoid obstacles. To determine the position of the robot, incremental encoders were used together with the odometric equations given by its kinematics.
The orientation of the differential robot is controlled by a discrete PID algorithm which is implemented inside a medium-high range microcontroller. The feedback is provided by a gyroscope, who measures the angle of rotation in the X-Y axes.
The desired position of the follower robot is given by the trajectory received from the leader robot through the Bluetooth communication protocol.
The results in the simulation show that a simple controller is sufficient to follow the desired trajectory while also having no steady state error. The dynamics of the actuators in the simulation are given by the actuators used in the prototype, so implementable actuating signals were produced.


## Objetivo 
Desarrollar un sistema móvil terrestre de seguimiento líder-seguidor sin contacto físico entre ellos, utilizando microcontroladores de gama media, mediante un algoritmo de control PI discreto. 
- Desarrollar un módulo seguidor capaz de navegar mediante el control de su orientación.
- Desarrollar un algoritmo que permita realizar el seguimiento del módulo líder. 
- Implementar un sistema que permita que los módulos sean capaces de mantener una distancia relativa entre sí previniendo el contacto físico
- Seleccionar sensores específicos para la navegación de ambos módulos. 

## Desarrollo del móvil líder
Se realiza el diseño del robot móvil en el software Proteus, como sistema de control se cuenta con el microcontrolador PIC16F886 el cual se encarga de en ejecutar el procesamiento de la información adjunta en él. La figura 4.7 muestra el flujo de información del sistema del robot líder, el cual consta del microcontrolador como pieza central, tres sensores que envían información, los puentes H que reciben comandos y el transmisor de Bluetooth. 
![Diagrama de líder](https://user-images.githubusercontent.com/72580785/174125972-150ff72b-7bd1-46f5-b467-7f855e638316.png)
Figura 4.7 Diagrama a bloques del módulo líder

## Desarrollo del móvil seguidor
Para este módulo móvil se cambian algunos componentes ya que este solo se guiaría del robot líder, pero necesita de una mayor cantidad de memoria respecto al microcontrolador del módulo móvil líder ya que en esta memoria se implementa el controlador PI y es indispensable obtener una rápida respuesta. La figura 4.15 ilustra que el módulo seguidor está constituido por un sensor que envía la aceleración que se convierte posteriormente en la orientación actual para la ley de control dentro del microcontrolador, el módulo bluetooth que envía la orientación deseada, y los motores que actúan como elementos finales de control.
![Diagrama de seguidor](https://user-images.githubusercontent.com/72580785/174127099-f74880ab-5f5b-4cdc-87eb-f44a661903dc.png)

### Algoritmo seguidor
Se diseña el algoritmo del módulo seguidor de tal forma que la variable controlada sea la orientación del robot diferencial tal como se ilustra en la figura 4.33. En donde el robot seguidor recibe a través del módulo Bluetooth la orientación deseada, su posición actual es medida con el acelerómetro/giroscópico MPU6050 para luego enviar el comando de control hacia los motores, o bien, los actuadores.
![Algoritmo-seguidor](https://user-images.githubusercontent.com/72580785/174127072-ced03c71-d4f8-4e68-b0a6-a4794c3fb9c8.png)

A continuación, se desarrollan los algoritmos del esquema anterior por partes.
La función que entrega la señal hacia los actuadores se llama “to_actuators(  )” y se construye con ayuda de la ecuación (2.4) como se muestra en el algoritmo 1.
![Algoritmo1](https://user-images.githubusercontent.com/72580785/174127650-27d9e5c8-e12a-49c6-bba2-529c5fa5ca44.PNG)

La función que entrega la orientación actual para su retroalimentación se llama “get_theta( )” y se construye con la ecuación (4.1) en el algoritmo 2.
![Algoritmo2](https://user-images.githubusercontent.com/72580785/174128167-991cbde4-5263-4f07-963d-9f8a34c6d26e.PNG)

El algoritmo control-seguidor del robot constituye el sistema de control completo, en donde se compara la posición actual con la posición deseada.
![Algoritmo3](https://user-images.githubusercontent.com/72580785/174128487-b78e293c-d175-469c-b92c-9fbe7e44a9f6.PNG)


