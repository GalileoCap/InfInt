BUILDD = './build'
BIN = f'{BUILDD}/infInt'

def Taskcompile():
  return {
    'deps': ['src/main.cc', 'src/infint.hpp'],
    'outs': [BUILDD, BIN],

    'actions': [
      f'mkdir -p {BUILDD}',
      f'g++ src/main.cc -o {BIN}',
    ],
  }

def Taskrun():
  return {
    'deps': [BIN],
    'skipRun': False,
    'capture': 2,

    'actions': [
      f'./{BIN}',
    ],
  }

