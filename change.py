import os

def change_file(file: str):
	if not file.rpartition('.')[2] in ['cpp', 'h', 'py', 'java']:
		return
	with open(file, 'r') as f:
		lines = f.readlines()

	useTab = 0
	use2Space = 0
	use3Space = 0
	use4Space = 0
	for line in lines:
		if line.startswith('\t'):
			useTab += 1
		if line.startswith('  ') and not line[2:].startswith(' '):
			use2Space += 1
		if line.startswith('   ') and not line[3:].startswith(' '):
			use3Space += 1
		if line.startswith('    ') and not line[4:].startswith(' '):
			use4Space += 1

	if use2Space + use3Space + use4Space == 0:
		return

	print(f'{file=} {useTab=} {use2Space=} {use3Space=} {use4Space=}')

	# with open(file, 'w') as f:
	#	 for line in lines:
	#		 f.write(line)

for root, dirs, files in os.walk('.'):
	for file in files:
		change_file(os.path.join(root, file))
