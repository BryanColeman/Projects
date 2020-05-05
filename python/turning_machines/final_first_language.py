'''
Bryan Coleman
BJC18BV

L = {a^ib^jc^k : k = i * j}
'''

import sys

def solution(tape):
    accept = True
    reject = False
    current = 0
    state = 'q0'
    head = tape[current]

    while head != ' ':
        if state == 'q0':
            if head == 'a':
                #mark our a with an x and move to a new state q1 and move head forward
                tape[current] = 'x'
                state = 'q1'
                current += 1
                head = tape[current]

            #if we have only one b we accept
            #because 0*1=0
            elif head == 'b':
                current += 1
                head = tape[current]
                if  head == ' ':
                    return accept
                else:
                    return reject

            #if start with a c meaning that there are no a's or b's(or there are after the c)
            #we reject either way because 0*0=0
            elif head == 'c':
                return reject

            #we accept empty strings
            #0*0=0
            elif head == ' ':
                return accept


        elif state == 'q1':
            if head == 'a':
                #move forward
                current += 1
                head = tape[current]

            elif head == 'b':
                #mark with a y and move to a new state q2 and move head forward
                tape[current] = 'y'
                state = 'q2'
                current += 1
                head = tape[current]

                if head == ' ':
                    #this is the case where there is one a, one b, and zero c's
                    return reject

            elif head == 'c':
                #must reject because it means we have no b's but have 1 or more a's and
                #anything greater then 0 times 0 is 0
                return reject

            #TODO might remove this
            elif head == ' ':
                #we accept because we have greater then 0 a's no b's and no c's
                #anything greater then0 times 0 is 0
                return accept

        elif state == 'q2':
            if head == 'a':
                #must reject because we can not have an a after a b
                return reject

            elif head == 'b' or head == 'z':
                #move forward
                current += 1
                head = tape[current]
                
                if head == ' ':
                    #this is the case where there are not enough c's to mark
                    #meaning that the number of c's is too low
                    return reject

            elif head == 'c':
                #mark with a z and we need to move to a new state q3
                tape[current] = 'z'
                state = 'q3'
                current -= 1
                head = tape[current]
            
        elif state == 'q3':
            if head == 'b' or head =='z':
                #move left
                current -= 1
                head = tape[current]

            elif head == 'y' or head == 'a' or head == 'x':
                #found our y now we move back right and mark with an x and move to state q2
                current += 1
                head = tape[current]

                if head == 'b':
                    #if we have a b we mark it with a y and move back to q2
                    tape[current] = 'y'
                    state = 'q2'
                    current += 1
                    head = tape[current]

                else:
                    #if we arive to a z we move to q4 and start with finding our next a
                    current -= 1
                    head = tape[current]
                    current -= 1
                    head = tape[current]
                    state = 'q4'

        elif state == 'q4':
            if head == 'y' or head == 'a':
                current -= 1
                head = tape[current]

            elif head == 'x':
                current += 1
                head = tape[current]

                if head == 'y':
                    #we know we are done with the 'a's so we have so we have all x's
                    #we also know we have all our y's
                    #so if we move left until we find a c we reject or a ' ' accept
                    #lets do this is a new state
                    current += 1
                    head = tape[current]
                    state = 'q5'

                if head == 'a':
                    #now we know we have another a so lets go ahead mark our x and unmark our y's lets do this
                    #in a new state
                    tape[current] = 'x'
                    current += 1
                    head = tape[current]
                    state = 'q6'

        elif state == 'q5':
            if head == 'y' or head == 'z':
                #we are only concered about c or space
                current += 1
                head = tape[current]

            if head == 'c':
                #if c we rejects because we know we have exhausted our a's and b's
                return reject

            if head == ' ':
                #if ' ' we know we exhausted our a's and b's but also used all our c's
                return accept

        elif state == 'q6':
            #remove our y's

            if head == 'a':
                #move on
                current += 1
                head = tape[current]

            if head == 'y':
                #unmark
                tape[current] = 'b'
                current += 1
                head = tape[current]

            if head == 'z':
                #we have unmarked all of our y's
                state = 'q3'

    #have reached our space
    while(current >= 0):
        current -= 1
        head = tape[current]

        if head == 'a' or head == 'b' or head == 'c':
            return reject

    return accept


if __name__ == '__main__':
    user_input = input('enter a string containing a\'s, b\'s, and c\'s \nto check if the string is the language L = {a^ib^jc^k : k = i * j} ->')
    flag = False

    for i in user_input:
        if i == 'a' or i == 'b' or i == 'c':
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

