# Function pointer returning function pointer

It is an exercise about function pointer programming!

<pre>
> make
> objdump -D -M intel function_pointer_return_function_pointer | less
</pre>
Let's disassemble it!

<pre>
000000000040057d <code>&lt;add&gt;</code>:
  40057d:	55                   	push   rbp
  40057e:	48 89 e5             	mov    rbp,rsp
  400581:	89 7d fc             	mov    DWORD PTR [rbp-0x4],edi
  400584:	89 75 f8             	mov    DWORD PTR [rbp-0x8],esi
</pre>
[rbp-0x8] is 2<br>
[rbp-0x4] is 5
<pre>
  400587:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
  40058a:	8b 55 fc             	mov    edx,DWORD PTR [rbp-0x4]
  40058d:	01 d0                	add    eax,edx
</pre>
return value is the sum of 5+2
<pre>
  40058f:	5d                   	pop    rbp
  400590:	c3                   	ret    
</pre>
<pre>
0000000000400591 <code>&lt;sub&gt;</code>:
  400591:	55                   	push   rbp
  400592:	48 89 e5             	mov    rbp,rsp
  400595:	89 7d fc             	mov    DWORD PTR [rbp-0x4],edi
  400598:	89 75 f8             	mov    DWORD PTR [rbp-0x8],esi
</pre>
[rbp-0x8] is 2<br>
[rbp-0x4] is 5
<pre>
  40059b:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
  40059e:	8b 55 fc             	mov    edx,DWORD PTR [rbp-0x4]
  4005a1:	29 c2                	sub    edx,eax
  4005a3:	89 d0                	mov    eax,edx
</pre>
return value is the difference of 5-2
<pre>
  4005a5:	5d                   	pop    rbp
  4005a6:	c3                   	ret    
</pre>

<pre>
00000000004005a7 <code>&lt;arithmetic&gt;</code>:
  4005a7:	55                   	push   rbp
  4005a8:	48 89 e5             	mov    rbp,rsp
  4005ab:	48 83 ec 20          	sub    rsp,0x20
  4005af:	89 f8                	mov    eax,edi
</pre>
In the first call:<br>
eax is '+'<br>
In the second call:<br>
eax is '-'<br>
<pre>
  4005b1:	89 75 e8             	mov    DWORD PTR [rbp-0x18],esi
  4005b4:	89 55 e4             	mov    DWORD PTR [rbp-0x1c],edx
</pre>
In the first and second call:<br>
edx is parameter '2'<br>
esi is parameter '5'<br>
so<br>
[rbp-0x18] is '5'<br>
[rbp-0x1c] is '2'<br>
<pre>
  4005b7:	88 45 ec             	mov    BYTE PTR [rbp-0x14],al
  4005ba:	0f be 45 ec          	movsx  eax,BYTE PTR [rbp-0x14]
  4005be:	83 f8 2b             	cmp    eax,0x2b
  4005c1:	74 07                	je     4005ca <arithmetic+0x23>
</pre>
compare eax and 0x2b '+' sign.<br>
if equal then jump to 4005ca<br>
<pre>
  4005c3:	83 f8 2d             	cmp    eax,0x2d
  4005c6:	74 23                	je     4005eb <arithmetic+0x44>
</pre>
compare eax and 0x2d '-' sign.<br>
if equal then jump to 4005eb<br>
<pre>
  4005c8:	eb 42                	jmp    40060c <arithmetic+0x65>
  4005ca:	8b 55 e4             	mov    edx,DWORD PTR [rbp-0x1c]
  4005cd:	8b 45 e8             	mov    eax,DWORD PTR [rbp-0x18]
  4005d0:	89 c6                	mov    esi,eax
  4005d2:	bf 54 07 40 00       	mov    edi,0x400754
  4005d7:	b8 00 00 00 00       	mov    eax,0x0
  4005dc:	e8 6f fe ff ff       	call   400450 <printf@plt>
</pre>
printf("%d+%d=",b,c);<br>
<pre>
  4005e1:	48 c7 45 f8 7d 05 40 	mov    QWORD PTR [rbp-0x8],0x40057d
</pre>
40057d is address of add function.<br>
and assign it to [rbp-0x8] fptr variable.<br>
<pre>
  4005e8:	00 
  4005e9:	eb 2b                	jmp    400616 <arithmetic+0x6f>
</pre>
jump to 400616<br>
<pre>
  4005eb:	8b 55 e4             	mov    edx,DWORD PTR [rbp-0x1c]
  4005ee:	8b 45 e8             	mov    eax,DWORD PTR [rbp-0x18]
  4005f1:	89 c6                	mov    esi,eax
  4005f3:	bf 5b 07 40 00       	mov    edi,0x40075b
  4005f8:	b8 00 00 00 00       	mov    eax,0x0
  4005fd:	e8 4e fe ff ff       	call   400450 <printf@plt>
</pre>
printf("%d-%d=",b,c);<br>
<pre>
  400602:	48 c7 45 f8 91 05 40 	mov    QWORD PTR [rbp-0x8],0x400591
</pre>
0x400591 is the address of sub function.<br>
<pre>
  400609:	00 
  40060a:	eb 0a                	jmp    400616 <arithmetic+0x6f>
</pre>
jump to 400616<br>
<pre>
  40060c:	bf 01 00 00 00       	mov    edi,0x1
  400611:	e8 6a fe ff ff       	call   400480 <exit@plt>
  400616:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
</pre>
content of [rbp-0x8] is the return value.<br>
<pre>
  40061a:	c9                   	leave  
  40061b:	c3                   	ret    
</pre>
<pre>
000000000040061c <code>&lt;main&gt;</code>:
  40061c:	55                   	push   rbp
  40061d:	48 89 e5             	mov    rbp,rsp
  400620:	48 83 ec 30          	sub    rsp,0x30
</pre>

open a stack frame.<br>
<pre>
  400624:	89 7d dc             	mov    DWORD PTR [rbp-0x24],edi
  400627:	48 89 75 d0          	mov    QWORD PTR [rbp-0x30],rsi
  40062b:	48 c7 45 f0 a7 05 40 	mov    QWORD PTR [rbp-0x10],0x4005a7
</pre>
rbp-0x10 is ffptr variable.<br>
0x4005a7 is arithmetic function address.<br>
<pre>
  400632:	00 
  400633:	c6 45 eb 2b          	mov    BYTE PTR [rbp-0x15],0x2b
</pre>
rbp-0x15 is operator variable.<br>
0x2b is '+' sign.<br>
<pre>
  400637:	0f be 4d eb          	movsx  ecx,BYTE PTR [rbp-0x15]
  40063b:	48 8b 45 f0          	mov    rax,QWORD PTR [rbp-0x10]
  40063f:	ba 02 00 00 00       	mov    edx,0x2
  400644:	be 05 00 00 00       	mov    esi,0x5
  400649:	89 cf                	mov    edi,ecx
  40064b:	ff d0                	call   rax
</pre>
edi & ecx are '+' sign.<br>
rax is 0x4005a7 address.<br>
edx is parameter '2'<br>
esi is parameter '5'<br>
and we call arithmetic function.<br>
let's go to 0x4005a7 address.<br>
<pre>
  40064d:	48 89 45 f8          	mov    QWORD PTR [rbp-0x8],rax
  400651:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
  400655:	be 02 00 00 00       	mov    esi,0x2
  40065a:	bf 05 00 00 00       	mov    edi,0x5
  40065f:	ff d0                	call   rax
</pre>
rax is the return value of the first arithmetic func call<br>
the value is the address of add function.<br>
so we call the add function and pass the paramaters '2' and '5'.<br>
let's go to 40057d address.<br>
<pre>
  400661:	89 45 ec             	mov    DWORD PTR [rbp-0x14],eax
  400664:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
  400667:	89 c6                	mov    esi,eax
  400669:	bf 62 07 40 00       	mov    edi,0x400762
  40066e:	b8 00 00 00 00       	mov    eax,0x0
  400673:	e8 d8 fd ff ff       	call   400450 <printf@plt>
</pre>
[rbp-0x14] is result variable.<br>
eax is return value 7<br>
so it prints 7<br>
<pre>
  400678:	c6 45 eb 2d          	mov    BYTE PTR [rbp-0x15],0x2d
  40067c:	0f be 4d eb          	movsx  ecx,BYTE PTR [rbp-0x15]
</pre>
rbp-0x15 is operator variable.<br>
0x2d is '-' sign.<br>
<pre>
  400680:	48 8b 45 f0          	mov    rax,QWORD PTR [rbp-0x10]
</pre>
rbp-0x10 is ffptr variable.<br>
it is 0x4005a7. (address of arithmetic function)<br>
<pre>
  400684:	ba 02 00 00 00       	mov    edx,0x2
  400689:	be 05 00 00 00       	mov    esi,0x5
  40068e:	89 cf                	mov    edi,ecx
  400690:	ff d0                	call   rax
</pre>
call arithmetic function and pass parameters '2' , '5' and '-'<br>
let's go to arithmetic again!<br>
<pre>
  400692:	48 89 45 f8          	mov    QWORD PTR [rbp-0x8],rax
  400696:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
  40069a:	be 02 00 00 00       	mov    esi,0x2
  40069f:	bf 05 00 00 00       	mov    edi,0x5
  4006a4:	ff d0                	call   rax
</pre>
rax is the return value of the second arithmetic func call<br>
the value is the address of sub function.<br>
so we call the sub function and pass the paramaters '2' and '5'.<br>
let's go to 400591 address.<br>
<pre>
  4006a6:	89 45 ec             	mov    DWORD PTR [rbp-0x14],eax
  4006a9:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
  4006ac:	89 c6                	mov    esi,eax
  4006ae:	bf 62 07 40 00       	mov    edi,0x400762
  4006b3:	b8 00 00 00 00       	mov    eax,0x0
  4006b8:	e8 93 fd ff ff       	call   400450 <printf@plt>
</pre>
[rbp-0x14] is result variable.<br>
eax is return value 3<br>
so it prints 3<br>

<pre>
  4006bd:	b8 00 00 00 00       	mov    eax,0x0
</pre>
return value of program is 0<br>
<pre>
  4006c2:	c9                   	leave  
  4006c3:	c3                   	ret    
  4006c4:	66 2e 0f 1f 84 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
  4006cb:	00 00 00 
  4006ce:	66 90                	xchg   ax,ax
</pre>

