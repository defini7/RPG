import subprocess


EMSDK_PATH = 'C:/SDK/emsdk'


if __name__ == '__main__':
    run = subprocess.run(f'{EMSDK_PATH}/emsdk activate latest & emrun Target/Web/Game/index.html', capture_output=True, shell=True)

    if len(run.stdout) > 0:
        print(run.stdout.decode(errors='ignore'))

    if len(run.stderr) > 0:
        print(run.stderr.decode(errors='ignore'))
