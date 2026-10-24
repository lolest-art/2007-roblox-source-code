# RBXGS Decompilation
A decompilation of [RBXGS (Roblox Grid Service) version 0.3.634.0](https://archive.org/download/rbxgssetup/S3FileHandler_RBXGSSetup_0.3.634.0.msi), currently focusing on specific critical components (v8kernel, v8world, etc.) for now, and will later expand out to other classes.

this is maked to build with modern MVSC tools!
## what build right now
- [x] physics engine
- [ ] render
- [ ] datamodel
- [ ] whole app folder  

##Building using MVSC 2026(Visual studio build tools 2026):
inside Client folder:
cmake --build . --config Release --parallel
when it build it should build rbx_engine.lib
ONLY PHYSICS ENGINE BUILD RIGHT NOW!!!
