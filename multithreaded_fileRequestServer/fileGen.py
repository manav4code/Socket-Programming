import lorem

loremFile = lorem.text()

filePath = "test.txt"

with open(filePath, 'w') as file:
    for i in range(0,100):
        file.write(loremFile)