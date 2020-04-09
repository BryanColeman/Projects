#bryan coleman
#bjc18bv

import csv
import enchant
import random
from collections import deque
import string

def generate(word):
    d = enchant.Dict('en_US')
    for i in range(len(word)):
        for letter in string.ascii_lowercase:
            candidate = word[:i] + letter + word[i+1:]
            if d.check(candidate):
                yield candidate

def find_shortest(start_word,end_word):
    q = deque([[start_word,1]])
    seen = set([start_word])
    while q:
        q_item = q.popleft()
        temp.append(q_item[0])
        for candidate in generate(q_item[0]):
            if candidate == end_word:
                return q_item[1] + 1
            elif candidate in seen:
                continue
            seen.add(candidate)
            q.append([candidate,q_item[1] + 1])
    return 0
    
def pick_word_pair():
    list_left = []
    list_right = []
    with open('Doublet.csv') as f:
        reader = csv.reader(f)
        for row in reader:
            list_left.append(row[0])
            list_right.append(row[1])
    our_random_number = random.randint(0,len(list_left)-1)
    return list_left[our_random_number],list_right[our_random_number]

def word_check_dict(user_list):
    d = enchant.Dict('en_US')
    for i in user_list:
        if not d.check(i):
            print(f'{i} is not a word in the dictionary. You lose.')
            return False
    return True

def word_check_rest(start_word,user_list):
    check = zip(start_word,user_list[0])
    counter = 0
    for j,k in check:
        if j != k:
            counter += 1
    if counter != 1:
        print('You have violated the one letter change constraint. You Lose.')
        return False
    for i in range(1,len(user_list)):
        counter = 0
        check = zip(user_list[i-1],user_list[i])
        for j,k in check:
            if j != k:
                counter += 1
        if counter != 1:
            print('You have violated the one letter change constraint. You Lose.')
            return False
    return True


def main():
    print('Welcome to the Doublet Game!')
    left_word, right_word = pick_word_pair()
    print(f'todays word pair is : {left_word} -> {right_word}')
    print('Please enter your word chain(not including the start and end word.)')
    print('Enter \'q\' when you\'re done')
    user_list = []
    user_word = input()
    while not user_word == 'q':
        user_list.append(user_word)
        user_word = input()
    if word_check_dict(user_list):
        print('All the entered words are in the dictionary')
        if word_check_rest(left_word,user_list):
            print('All the words follow the one letter contraint')
            check = zip(user_list[len(user_list)-1],right_word)
            counter = 0
            for j,k in check:
                if j != k:
                    counter +=1
            if counter == 1:
                print('You have successfully solved the problem.')
                if(len(user_list) < find_shortest(left_word,right_word)):
                    print('You have solved the problem with the smallest number of words. Congrats')
                else:
                    print('you have not solved the problem in the smallest number of words. You lose.')
            else:
                print('You have violated, the one letter change constraint. You lose.')

if __name__ == '__main__':
    main()
