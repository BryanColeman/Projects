'''
Bryan Coleman
BJC18BV

membership question for L = {w E {0,1}* : w is a binary palendrome}
'''

import sys

def solution(tape):
    accept = True
    reject = False
    state = 'q0'
    current = 0
    head = tape[current]

    while True:

        if state == 'q0':

            if head == ' ':
                #empty string, accept
                return accept

            else:
                #hold onto our value to compare
                #set the var at the head to x
                #move to state q1
                memory = head
                tape[current] = 'x'
                state = 'q1'
                current += 1
                head = tape[current]

                if head == ' ':
                    #quickly check to see if we only have one variable which we accept
                    return accept

        elif state == 'q1':
            if head == '1' or head == '0':
                #roll through the tape if we hit a 1 or 0
                current += 1
                head = tape[current]

            if head == ' ' or head == 'y':
                #if we find a space or y we need to roll back one
                #compare to memory
                #reject if no match
                #change var to y if there is a match and move to state q2
                current -= 1
                head = tape[current]
                
                if head == 'x':
                    #we have found an odd palendrome
                    #the last x mark is arbitray
                    #example 10101 and 10001 are both accepted
                    return accept

                if head == memory:
                    tape[current] = 'y'
                    state = 'q2'
                    current -= 1
                    head = tape[current]
                else:
                    return reject

        elif state == 'q2':
            if head == '1' or head == '0':
                #roll through to the left if we hit a 1 or 0
                current -= 1
                head = tape[current]

            if head == 'x':
                current += 1
                head = tape[current]

                if head == 'y':
                    #this is the case were we moved forward and immediatly found a y
                    #meaning we have a even palidrome
                    return accept

                else:
                    #else we mark with an x and move back to state q1
                    memory = head
                    tape[current] = 'x'
                    current += 1
                    head = tape[current]
                    state = 'q1'


if __name__ == '__main__':
    user_input = str(input('enter a string containing 1\'s and 0\'s to see if they are in the language L = L = {w E {0,1}* : w is a binary palendrome} -> '))
    flag = False

    for i in user_input:
        if i == '1' or i == '0':
            pass
        else:
            flag = True
    if(flag):
        print('you\'re string contains invalid char\'s')
        sys.exit()

    tape = list(user_input)
    tape.append(' ')
    if solution(tape):
        print('String is accepted')
    else:
        print('String is NOT accepted')
