# Lexical Analyser for Simple C Programs
import os
import sys


# Method to check if a string is number or not
def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        pass
    try:
        import unicodedata
        unicodedata.numeric(s)
        return True
    except (TypeError, ValueError):
        pass
    return False


try:
    # Reading keywords into a list from keywords.txt file
    keyword_list = [line.rstrip('\n') for line in open('keywords.txt')]
except FileNotFoundError:
    print('\nkeywords.txt not found.')
    sys.exit()
# Other lists for arithmetic,relational and assignment operator
arith_op_list = ['+', '-', '*', '/']
rel_op_list = ['<', '>']
assign_op = '='
punc_symbols = [';', ',', '(', ')', '{', '}']
white_space = [' ', '\n']
# Number and Alphabet list
num_list = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
alphabet = 'qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'

num_buffer = ''
word_buffer = ''

next_char = ''
flag = 0
invalid_flag = 0
row = 1
column = 1
token_no = 0

in_filename = input('\nEnter name of the C program: ')
try:
    input_file = open(in_filename, 'r')
except FileNotFoundError:
    print('\nFile not found :: ' + in_filename)
    sys.exit()

# Slicing out only the filename, without extension
out_filename = str(os.path.splitext(in_filename)[0]) + '.csv'
# Opening the output file with extension CSV
try:
    output_file = open(out_filename, 'w')
    # Writing header to CSV file
    header = 'Token No.' + ',' + 'Token' + ',' + 'Token Type' + ',' + 'Row' + ',' + 'Column' + '\n'
    output_file.write(header)
except PermissionError:
    print('\nPermission denied for ' + out_filename)
    print('\nClose any other application using ' + out_filename)
    sys.exit()

while True:
    # Reading 1 byte at a time
    if flag is 0:
        character = input_file.read(1)
    # Getting the next character if it is already read
    else:
        character = next_char
    if not character:
        print('\n\nLexical Analysis Complete.')
        break
    else:
        # If the current character is in white space list
        if character in white_space:
            flag = 0
            # If it is a new line, increment row, reinitialize column as 1
            if character is '\n':
                row += 1
                column = 1
            # If it is only a space, increment column only
            elif character is ' ':
                column += 1
        # If the current character is in arithmetic operator list
        elif character in arith_op_list:
            # If it is a backslash, three possibilities are there
            if character is '/':
                flag = 1
                next_char = input_file.read(1)
                # If next character is also a backslash, then we have a single line comment
                if next_char is '/':
                    while True:
                        next_char = input_file.read(1)
                        if next_char is not '\n':
                            continue
                        else:
                            break
                    row += 1
                    column = 1
                # If next character is a star, then we have a multi line comment
                elif next_char is '*':
                    cur_char = input_file.read(1)
                    later_char = input_file.read(1)
                    # Loop and skip until multi line comment ends
                    while True:
                        # If we have */ combination at some point, multi-line comment ends
                        if cur_char is '*' and later_char is '/':
                            flag = 0
                            break
                        # If newline occurs, increment row and set column equal to 1
                        elif later_char is '\n':
                            row += 1
                            column = 1
                        # If we have back to back 2 newlines, increment row by 2 and set column equal to 1
                        elif cur_char is '\n' and later_char is '\n':
                            row += 2
                            column = 1
                        cur_char = later_char
                        later_char = input_file.read(1)
                # If the above doesn't occur, that means current character is arithmetic operator only
                else:
                    column += 1
                    token_no += 1
                    output_file.write(
                        str(token_no) + ',' + str(character) + ',' + 'Arithmetic Op' + ',' + str(row) + ',' + str(
                            column) + '\n')
            # This condition is for arithmetic operators other than divide or backslash
            else:
                flag = 0
                column += 1
                token_no += 1
                output_file.write(
                    str(token_no) + ',' + str(character) + ',' + 'Arithmetic Op' + ',' + str(row) + ',' + str(
                        column) + '\n')
        # If the current character is in relational operator list
        elif character in rel_op_list:
            flag = 0
            column += 1
            token_no += 1
            output_file.write(str(token_no) + ',' + str(character) + ',' + 'Relational Op' + ',' + str(row) + ',' + str(
                column) + '\n')
        # If the current character is assignment operator
        elif character is assign_op:
            flag = 0
            invalid_flag = 1    # This flag is for checking if a ID is on LHS or RHS of equal sign
            column += 1
            token_no += 1
            output_file.write(str(token_no) + ',' + str(character) + ',' + 'Assignment Op' + ',' + str(row) + ',' + str(
                column) + '\n')
        # If the current character is in punctuation symbols list
        elif character in punc_symbols:
            if character is ';':
                invalid_flag = 0    # Semicolon resets the flag for ID position checking
            flag = 0
            column += 1
            token_no += 1
            if character is ',':
                output_file.write(
                    str(token_no) + ',' + '","' + ',' + 'Punctuation Symbol' + ',' + str(row) + ',' + str(
                        column) + '\n')
            else:
                output_file.write(
                    str(token_no) + ',' + str(character) + ',' + 'Punctuation Symbol' + ',' + str(row) + ',' + str(
                        column) + '\n')
        # If the current character is in number list
        elif character in num_list:
            flag = 1
            num_buffer += character
            next_char = input_file.read(1)
            column += 1
            # Put character in number buffer until we have number or letter
            while next_char in num_list or next_char in alphabet:
                character = next_char
                num_buffer += character
                next_char = input_file.read(1)
                column += 1
            token_no += 1
            # If number buffer is a number then write type as number
            if is_number("".join(num_buffer)):
                output_file.write(
                    str(token_no) + ',' + str(num_buffer) + ',' + 'Number' + ',' + str(row) + ',' + str(column) + '\n')
            # If its not a number then it may be a Invalid Number or Invalid Identifier according to the position
            # it has i.e. RHS or LHS with respect to assignment operator
            else:
                if invalid_flag is 1:
                    output_file.write(
                        str(token_no) + ',' + str(num_buffer) + ',' + 'Invalid Number' + ',' + str(row) + ',' + str(
                            column) + '\n')
                else:
                    output_file.write(
                        str(token_no) + ',' + str(num_buffer) + ',' + 'Invalid Identifier' + ',' + str(row) + ',' + str(
                            column) + '\n')
            num_buffer = ''
        # If the current character is in alphabet list
        elif character in alphabet:
            flag = 1
            word_buffer += character
            next_char = input_file.read(1)
            column += 1
            # Put character in word buffer until we have number or letter
            while next_char in alphabet or next_char in num_list:
                character = next_char
                word_buffer += character
                next_char = input_file.read(1)
                column += 1
            # Check if word buffer contains a keyword
            if word_buffer in keyword_list:
                token_no += 1
                # Write token details, type as Keyword
                output_file.write(str(token_no) + ',' + str(word_buffer) + ',' + 'Keyword' + ',' + str(row) + ',' + str(
                    column) + '\n')
            # If its not a keyword then its a identifier
            else:
                token_no += 1
                output_file.write(
                    str(token_no) + ',' + str(word_buffer) + ',' + 'Identifier' + ',' + str(row) + ',' + str(
                        column) + '\n')
            word_buffer = ''
# Close input and output files
input_file.close()
output_file.close()
