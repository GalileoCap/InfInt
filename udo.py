BIN = 'infInt'

def Taskcompile():
  return {
    'deps': ['main.cc'],

    'actions': [
      f'g++ main.cc -o {BIN}',
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

