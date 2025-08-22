set files=src\glad.c src\main.c
set libs=E:\lib\SDL2main.lib E:\lib\SDL2.lib E:\lib\freetype.lib

CL /Zi /I E:\include %files% /link %libs% /OUT:mygame.exe
