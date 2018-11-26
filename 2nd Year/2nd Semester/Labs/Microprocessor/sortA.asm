
lda 204fH
mov b,a
lxi d,204fH

third: inx d
dcr a
jnz third
mov b,c

fourth: mov b,c
lxi h,2050H

second: ldax d
cmp m
jc first
sta 2100H
mov a,m
stax d
lda 2100H
xchg
stax d
xchg

first: inx h
dcr b
jnz second
dcx d
dcr c
jnz fourth


hlt