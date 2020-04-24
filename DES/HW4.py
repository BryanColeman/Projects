'''
Bryan Coleman
BJC18BV
The program in this file is the individual work of Bryan Coleman
'''

from random import seed,randint
from datetime import datetime
import string


'''
All the boxes that we will need to permute values
'''

shift = [1,1,2,2,2,2,2,2,
        1,2,2,2,2,2,2,1]

PC = [14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32]

initial_perm = [58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7]

expand = [32, 1 , 2 , 3 , 4 , 5 , 4 , 5,
        6 , 7 , 8 , 9 , 8 , 9 , 10, 11,
        12, 13, 12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21, 20, 21,
        22, 23, 24, 25, 24, 25, 26, 27,
        28, 29, 28, 29, 30, 31, 32, 1 ]

sbox =  [['1110','0100','1101','0001','0010','1111','1011','1000','0011','1010','0110','1100','0101','1001','0000','0111'],
        ['0000','1111','0111','0100','1110','0010','1101','0001','1010','0110','1100','1011','1001','0101','0011','1000'],
        ['0100','0001','1110','1000','1101','0110','0010','1011','1111','1100','1001','0111','0011','1010','0101','0000'],
        ['1111','1100','1000','0010','0100','1001','0001','0111','0101','1011','0011','1110','1010','0000','0110','1101']]

inter_perm = [16,  7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2,  8, 24, 14, 32, 27,  3,  9,
        19, 13, 30,  6, 22, 11,  4, 25]

final_perm = [40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25]

def split_string_and_make_binary(plain_text):
    '''
    split the text into lengths of 8
    if the last string is not of length 8 note that
    then format using 08b, which makes give it the format 00000000 for 0
    then if we had a length of less then 8 for the last string buff with zeros

    :params:
            plain_text: string that we are breaking up

    return: 
            binary_list:list of 64 bit binary numbers
    '''
    splits = len(plain_text) // 8
    extra = len(plain_text) % 8
    split_list = [plain_text[i*8:(i+1)*8] for i in range(splits)]
    if extra > 0:
        split_list.append(plain_text[splits*8:])
    binary_list = [(''.join(format(ord(c), '08b') for c in i)) for i in split_list]
    if extra > 0:
        temp = ''
        for _ in range(8 - extra):
            temp = temp + '00000000'
        temp = temp + binary_list[-1]
        binary_list[-1] = temp
    return binary_list

def encrypt(plain_text, key):
    '''
    take in a message and encrypt it
    :params: 
            plain_text: message we want to encrypt
            key: key that we will use for encrypt and decrypt, random for each string
    :return:
            cipher_text: ciphered text
    '''
    
    split_list = split_string_and_make_binary(plain_text)

    cipher_text = ''
    for i in split_list:
        current = DES(i,key)
        for j in range(8):
            temp = current[j*8:j*8+8]
            cipher_text = cipher_text + chr(int(temp,2))

    return cipher_text

def decrypt(cipher_text, key):
    '''
    take in a ciphered message and decrypt it
    :params:
            cipher_text: message we want to decrypt
            key: key that we will use for encrypt and decrypt, random for each string
    :return:
            plain_text: decrypted message
    '''
    
    split_list = split_string_and_make_binary(cipher_text)

    plain_text = ''
    for i in split_list:
        current = DES(i,key)
        for j in range(8):
            temp = current[j*8:j*8+8]
            plain_text = plain_text + chr(int(temp,2))

    return plain_text

def DES(number, key):
    '''
    :params:
            number: a 64 bit binary number that represents either a plain_text or ciphered_text
            key: key that we will use for encrypt and decrypt, random for each string
    :return:
    '''
    
    first_perm = ''
    for i in range(64):
        first_perm = first_perm + number[initial_perm[i] - 1]

    left = first_perm[:32]
    right = first_perm[32:]

    for i in range(16):
        key = key[shift[i]::] + key[:shift[i]:]
        bit_key = ''
        for j in range(48):
            bit_key = bit_key + key[PC[j] - 1]

        expand_right = ''
        for j in range(48):
            expand_right = expand_right + right[expand[j] - 1]
    
        xor = int(expand_right,2) ^ int(bit_key,2)
        right_xor_key = '{0:0{1}b}'.format(xor,len(expand_right))
        
        collapse_right = ''
        for j in range(8):
            temp = right_xor_key[j*6:j*6+6]
            find_row = temp[0] + temp[-1]
            row = int(find_row, 2)
            find_col = temp[1:5]
            col = int(find_col, 2)
            res = sbox[row][col]
            collapse_right = collapse_right + res

        permute_right = ''
        for j in range(32):
            permute_right = permute_right + collapse_right[inter_perm[j] - 1]

        xor = int(left,2) ^ int(right,2)
        result = '{0:0{1}b}'.format(xor,len(left))
        left = result
        if i != 15:
            left,right = right,left

    bring_back = left + right

    last_perm = ''
    for i in range(64):
        last_perm = last_perm + bring_back[final_perm[i] - 1]

    return last_perm


def main():
    print('DES Implementation:')
    plain_text = input('Enter text to encrypt (\"Exit\" to quit): ')
    while(plain_text.lower() != 'exit'):
        key = [str(randint(0,1)) for _ in range(56)]
        print(key)

        print(f'Encrypted text: {encrypt(plain_text,key)}')
        print(f'Decrypted text: {decrypt(encrypt(plain_text,key),key)}')

        plain_text = input('Next text: ') 

if __name__ == '__main__':
    seed(datetime.now())
    main()
