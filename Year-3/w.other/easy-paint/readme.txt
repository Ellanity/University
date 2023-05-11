# ## Compile project into exe file ## #
url:
https://stackoverflow.com/questions/54210392/how-can-i-convert-pygame-to-exe
comands:
pyinstaller --onefile --noconsole easy-paint.py --collect-data assets/chars --collect-data assets/tiles --collect-data assets/fonts
pyinstaller easy-paint.py --onefile --noconsole --collect-data assets/images
pyinstaller easy-pain.spec