import subprocess
from constants import bin_file

words = raw_input('Enter words in single line: ')
words = words + " -"

g_to_p = subprocess.Popen(bin_file, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
g_to_p.stdin.write(words)
g_to_p.stdin.close()

output = g_to_p.stdout.read()
output = output.strip()
output = output.replace(" ", "")
output = output.replace("\n", " ")

festival = subprocess.Popen('festival --tts', shell=True, stdin=subprocess.PIPE)
festival.stdin.write(output)
festival.stdin.close()