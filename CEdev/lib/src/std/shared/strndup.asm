	.def _strndup
	.ref __frameset
	.ref _strlen
	.ref _malloc
	.ref _memcpy
	.assume adl=1

_strndup:
	ld	hl,-6
	call	__frameset
	ld	bc,(ix+6)
	push	bc
	call	_strlen
	ld	(ix+-3),hl
	ex	de,hl
	ld	hl,(ix+9)
	or	a,a
	sbc	hl,de
	jr	nc,Greater
	ld	hl,(ix+9)
	ld	(ix+-3),hl
Greater:
	ld	bc,(ix+-3)
	inc	bc
	push	bc
	call	_malloc
	ld	(ix+-6),hl
	add	hl,bc 
	or	a,a 
	sbc	hl,bc
	jr	z,MallocFail
	ld	bc,(ix+-3)
	ld	hl,(ix+-6)
	add	hl,bc
	ld	(hl),0
	or	a,a
	sbc	hl,bc
	push	bc
	ld	bc,(ix+6)
	push	bc
	push	hl
	call	_memcpy
MallocFail:
	ld	sp,ix
	pop	ix
	ret
