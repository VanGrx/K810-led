# K810-led
Customizable app that uses [g810-led](https://github.com/MatMoul/g810-led) and KDE [KIdleTime](https://github.com/KDE/kidletime).

## Usage
Install and create *.k810* file in your home folder. Example file can be viewed [here](example.k810).
Add the application to KDE Autostart or hook the application to other autostart services.

## Config file
Each line represents an effect that will be triggered after the given time. If the given time is 0, the keyboard will be set to that effect after it returns from the idle state.

Each line contains:
- Time after which the effect is activated in milliseconds
- Effect type (l - light intensity, b - breathing)
- Max intensity of the light
- Numerator with whom the intensity is multiplied
- Denominator with whom the intensity is divided
- (if effect type is breathing) Lenght of the effect cycle in seconds

Numerator and denominator are added for easier setting of the intensity. For example, if you would like to have 10 stages of light reduced, you can add denominator 10 and then change the numerator from 10 to 1 for a linear decrease of the intensity.

Every bad-configured line will result in that line being ignored by the parser.
