#MIT License(MIT)

#     CertToHex.py Version 1.0.0        #

#     Copyright(c) 2018 Mike Simpson      #

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.

import binascii
filename = 'howMyssl.cer'
with open(filename, 'rb') as f:
    content = f.read()

hexData = binascii.hexlify(content)
hexList = list(''.join(hexData))
print('// '+filename)
print('const unsigned char caCert[] PROGMEM = {\n')
outString = ''
caCertLen = 0


x = len(hexList)
for i in range(0, (x-1), 2):
    first = hexList[i]
    second = hexList[i+1]
    outString = outString+ '0x' + first + second + ', '
    caCertLen = caCertLen + 1
    if i%24 > 20 :
        outString = outString + '\n'

outString = outString[:-2] #remove last comma and space

print(outString+'};\n')
print('const unsigned int caCertLen = ' + str(caCertLen) + ';')
