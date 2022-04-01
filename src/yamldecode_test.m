sep = "****************************************\n"

printf(sep)
printf("Ex.1\n\n")
s = "{foo: 1, bar: [2, 3]}"
yamldecode(s)

printf(sep)
printf("Ex.2\n\n")
s = "v2: 123\n\
v3: 123.45\n\
v4: 'abc'\n\
seq:\n\
  - 101\n\
  - 102\n\
  - 103\n\
map:\n\
  1001: 2001\n\
  1002: 2002\n\
  1003: 2003"
yamldecode(s)

printf(sep)
printf("Ex.3 (supposed to send error msg.)\n\n")
s = ""
yamldecode(s)
