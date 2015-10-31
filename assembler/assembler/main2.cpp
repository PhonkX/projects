#include <iostream>

using namespace std;


__declspec(naked)
int f(int a, int b) {
	__asm {
		push ebp
		mov ebp, esp
		mov eax, [ebp + 8]
		add eax, [ebp + 12]
		pop ebp
		ret
	}
}

__declspec(naked)
int fact(int n) {
	__asm {
		push ebp
		mov ebp, esp
				
		mov eax, [ebp + 8]
		cmp eax, 1

		jle L1
		
		dec eax
		push eax
		
		call fact
		add esp, 4
		
		mul dword ptr [ebp+8]
		jmp L2
	L1:	mov eax, 1
	L2:	pop ebp
		ret
	}
}


__declspec(naked)
void reverse(int *a, int n) {

	__asm {

		push ebp
		mov ebp, esp

		mov esi, [ebp + 8] //p0
		mov edi, [ebp + 12]
		dec edi //n-1
		shl edi, 2 // 4*(n-1)
		add edi, esi // p1

L2:		cmp esi, edi
		jae L1

		mov eax, [esi]
		mov ebx, [edi]
		mov [edi], eax
		mov [esi], ebx
		add esi, 4
		sub edi, 4
		jmp L2

L1:     pop ebp
		ret
	}
}

void reverse1(int *a, int n) {
	int *p0 = a, *p1 = a + n -1;
	while (p0 < p1) {
		swap(*p0++, *p1--);
	}
}


int main() {

	int n;

	/*__asm {
		push 2
		push 1
		call f
		add esp, 8
		mov n, eax
	}*/

	/*__asm {
	push 5
	call fact
	add esp, 4
	mov n, eax
	}*/

	int a[7] = { 0, 1, 2, 3, 4, 5, 6 };
	int b[5] = { 0, 1, 2, 3, 4 };
	int c[4] = { 0, 1, 2, 3 };
	int l = 4;
	int k = 5;
	n = 7;
	__asm {
	push 7
	lea eax, a
	push eax
	call reverse
	add esp, 8
	}
	reverse1(b, k);
	reverse1(c, k);
	//cout << n << endl;
	for (int i = 0; i < n; ++i) {
		cout << a[i] << ' ';
	}
	for (int i = 0; i < k; ++i) {
		cout << b[i] << ' ';
	}
	for (int i = 0; i < l; ++i) {
		cout << c[i] << ' ';
	}
	cout << endl;
	return 0;
}