# Terrarium
## Description:


### Dependencies:
```
brew install meson
brew install ninja
brew install sdl2
brew install sdl2_image
```


## Setup:
`meson setup builddir`

## How to Build:
`cd builddir`
`meson compile && ./botwar`

Bug structure

Bug:
 - Organs
    - Reactions
        - Any two chemicals coming together to become any two other chemicals.
    - Emitter
        - Adds to the concentration of any given chemical if condition is met.
    - Receptors
        - Can modify a output of reaction or emmitter if condition is met.  
        - Can be set to modify all reactions in organ
 - Biochemistry
    - Chemical
        - Current Concentration
        - Decay Rate
        - Name
 - Laws of Nature
    - Systems that manage the rules of nature
        - Damage organs when certain chemicals are present.  For an organ to be resistant to damage it needs to process said chemical.
        - Decay the chemicals at their appropriate rates
        - Introduce chemicals based on organism's surroundings.  IE Provide's o2, co2, co, h2o etc from the environment.  In any given frame the current concentration added is a ration of surrounding chemical emmitters in the environment.  