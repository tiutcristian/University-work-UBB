# Problem 4


def valid(k: int, st: list) -> bool:
    if k == 3 and st[3] == 'X':
        return False
    if st[k] == 1:
        for i in range(k):
            if st[i] == 1:
                return False
    return True


def back_rec(k: int, st: list):
    for i in [1, 'X', 2]:
        st[k] = i
        if valid(k, st):
            if k == 3:
                print(*st, sep=" ")
            else:
                back_rec(k + 1, st)


def back_it():
    st = [0]
    while len(st) > 0:
        is_successor = False
        is_valid = False

        if len(st) <= 4:  # if desired length not exceeded

            # do ... while
            is_successor = (st[len(st)-1] != 2)  # is successor if top of stack is not 2
            if is_successor:  # increase the value for the top of the stack
                if st[len(st)-1] == 0:
                    st[len(st) - 1] = 1
                elif st[len(st)-1] == 1:
                    st[len(st) - 1] = 'X'
                else:  # top_of_stack == X
                    st[len(st) - 1] = 2
                is_valid = valid(len(st) - 1, st)  # verify validity of the new element

            while is_successor and not is_valid:
                is_successor = (st[len(st) - 1] != 2)  # is successor if top of stack is not 2
                if is_successor:  # increase the value for the top of the stack
                    if st[len(st) - 1] == 0:
                        st[len(st) - 1] = 1
                    elif st[len(st) - 1] == 1:
                        st[len(st) - 1] = 'X'
                    else:  # top_of_stack == X
                        st[len(st) - 1] = 2
                    is_valid = valid(len(st) - 1, st)  # verify validity of the new element

        if is_successor:        # if is successor and is valid (if no valid successor found,
            if len(st) == 4:    # then is_successor will be set to False)
                print(*st, sep=" ")  # print if stack has desired length
            else:
                st.append(0)  # add a new element to the stack
        else:
            st.pop()  # successor doesn't exist, hence pop the top of the stack


print("\nRecursive backtracking:")
numbers = [0] * 4
back_rec(0, numbers)
print("\nIterative backtracking:")
back_it()
