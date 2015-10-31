//#include <iostream>
//
//using namespace std;
//
//int f(int k)
//{
//	__asm
//	{
//		mov ecx, k
//		mov eax, 1
//	L:  mul ecx
//		loop L
//	}
//}
//
//int f1(int k)
//{
//	__asm
//	{
//		mov ecx, k
//		mov eax, 1
//	L:  mul ecx
//		dec ecx
//		jnz L
//	}
//}
//
//int sum(int *a, int n)
//{
//	__asm
//	{
//		mov ebx, a;
//		mov ecx, n; 
//		mov eax, 0
//	L:  add eax, [ebx]
//		add ebx, 4
//		loop L
//	}
//}
//
//int rol(unsigned int x, unsigned int n)
//{
//	__asm
//	{
//		mov eax, x
//		mov ebx, eax
//		mov ecx, n
//		shl eax, cl
//		sub ecx, 32
//		neg ecx
//		shr ebx, cl
//		or eax, ebx
//	}
//}
//
//int amin(int x, int y, int z)
//{
//	__asm
//	{
//		mov eax, x
//		cmp eax, y
//		jle L1
//		mov eax, y
//	L1:	cmp eax, z
//		jle L2
//		mov eax, z
//	L2:
//
//	}
//}
//
//int sign1(int x)
//{
//	__asm
//	{
//		mov eax, x
//		cmp eax, 0
//		je Done
//		jl L
//	L:	mov eax, 1
//		jmp Done
//		mov eax, -1
//  Done:
//	}
//}
//
//int sign2(int x)
//{
//	if (x > 0)
//		return 1;
//	else if (x < 0)
//		return -1;
//	else return 0;
//}
//
//
//
//
//void scopy(char* s, char* d, int n){
//	__asm {
//		mov ecx, n
//		mov esi, s
//		mov edi, d
//		cld
//		rep movsb
//	}
//}
//
//int myStrLen(char *s){
//
//	__asm {
//		mov al, 0
//		mov edi, s
//		cld
//		mov ecx, -1
//		repne scasb
//		mov eax, ecx
//		not eax
//		dec eax
//	}
//}
//
//
//
//void mystrcpy(char *s, char *d){
//	__asm {
//		mov al, 0
//		mov edi, s
//		cld
//		mov ecx, -1
//		repne scasb
//		not ecx
//		mov esi, s
//		mov edi, d
//		rep movsb
//	}
//}
//
//
//void mystrcpy2(char *s, char *d){
//	__asm{
//		mov esi, s
//		mov edi, d
//		cld
//
//	L1:	lodsb
//		stosb
//		cmp al, 0
//		jnz L1		
//	}
//}
//
//char* mystrcat(char *s, char *d){
//	__asm {
//		mov esi, s
//		mov edi, d
//		mov al, 0
//		cld
//		mov ecx, -1
//		repne scasb
//		dec edi
//   L1 : lodsb
//		stosb
//		cmp al, 0
//		jnz L1
//		mov eax, d
//	}
//}
//
//int main()
//{
//	/*int k = 7;
//	cout << f(k) << endl;
//	int a[5] = { 1,2,5,9,10 };
//	int n = 5;
//	cout << sum(a, n) << endl;*/
//	//cout << amin(8, 9, 10) << endl;
//	/*cout << sign1(10) << endl;
//	cout << sign2(10) << endl;
//	cout << sign2(0) << endl;
//	cout << sign2(-10) << endl;*/
//	//cout << f1(3) << endl;
//	//cout << rol(15, 4) << endl;
//
//
//	/*char *s = "abcd";
//	char d[5] = { 0 };
//
//
//
//	scopy(s, d, 4);
//	cout << d;*/
//
//	//cout << myStrLen("") << endl;
//	char *s = "abcd";
////	char d[5] = { 0 };
//	//mystrcpy(s, d);
//	//cout << d << endl;
//
//	//mystrcpy2(s, d);
//	//cout << d << endl;
//	char d[1000] = {0};
//	mystrcpy2("efgh", d);
//
//	cout << mystrcat("abcd", d) << endl;
//
//	return 0;
//}

