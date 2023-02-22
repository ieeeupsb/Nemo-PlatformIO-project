import sys

Import("env")
try:
    Import("projenv")
except:
    projenv = env

for env_ in (env, projenv):
    cxx_flags = env_.subst("$CXXFLAGS $CCFLAGS")
    if "-std=" not in cxx_flags:
        env_.Append(CXXFLAGS=["-std=c++11"])

# Force POSIX Threads on Linux
if "linux" in sys.platform and not env.PioPlatform().is_embedded():
    globalenv = DefaultEnvironment()
    globalenv.Append(LINKFLAGS=["-pthread"])
