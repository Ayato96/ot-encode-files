-- this is the first file executed when the application starts
-- we have to load the first modules form here

-- setup logger
g_logger.setLogFile(g_resources.getWorkDir() .. g_app.getCompactName() .. ".log")

-- search all packages
g_resources.addSearchPath(g_resources.getWorkDir() .. "data/data", true)
g_resources.addSearchPath(g_resources.getWorkDir() .. "data/modules", true)
g_resources.addSearchPath(g_resources.getWorkDir() .. "data/pokemon", true)
g_resources.addSearchPath(g_resources.getWorkDir() .. "data/mods", true)
g_resources.addSearchPath(g_resources.getWorkDir() .. "data/otbuild", true)

g_resources.addSearchPath(g_resources.getWorkDir() .. "data/modules.otpkg", true)
g_resources.addSearchPath(g_resources.getWorkDir() .. "data/pokemon.otpkg", true)
g_resources.addSearchPath(g_resources.getWorkDir() .. "data/mods.otpkg", true)
g_resources.addSearchPath(g_resources.getWorkDir() .. "data/data.otpkg", true)

-- setup directory for saving configurations
g_resources.setupUserWriteDir(g_app.getCompactName())

-- load settings
g_configs.loadSettings("/config.cfg")
g_configs.load("/data.bin")

g_modules.discoverModules()

-- libraries modules 0-99
g_modules.autoLoadModules(99)
g_modules.ensureModuleLoaded("corelib")
g_modules.ensureModuleLoaded("gamelib")

-- client modules 100-499
g_modules.autoLoadModules(499)
g_modules.ensureModuleLoaded("client")

-- game modules 500-999
g_modules.autoLoadModules(999)
g_modules.ensureModuleLoaded("game_interface")

-- mods 1000-9999
g_modules.autoLoadModules(9999)