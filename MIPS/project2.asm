.data
	# _____DU LIEU INPUT_____
	TIME: #bien luu chuoi ngay thang nam
		.space 1024 
	TIME_2: 
		.space 1024 
	inputString: #bien luu chuoi nhap vao
		.space 1024

	inputMsg_day: 
		.asciiz "Nhap ngay DAY: "
	inputMsg_month: 
		.asciiz "Nhap thang MONTH: "
	inputMsg_year: 
		.asciiz "Nhap nam YEAR: "
	inputMsg_Invalid:
		.asciiz "Du lieu khong hop le. Moi nhap lai.\n"
	inputMsg_time2:
		.asciiz "Nhap chuoi TIME_2:\n"
		

	# _____MENU LUA CHON_____	
	separateMsg:
		.asciiz "\n--------------------------------------------------\n"
	optionsMenu:
		.asciiz "----Ban hay chon 1 trong cac thao tac duoi day----\n"
	option1:
		.asciiz "1. Xuat chuoi TIME theo dinh dang DD/MM/YYYY\n"
	option2:
		.asciiz "2. Xuat chuoi TIME thanh mot trong cac dinh dang sau\n   A. MM/DD/YYYY\n   B. Month DD, YYYY\n   C. DD Month, YYYY\n"

		type_of_option2:
			.asciiz "Chon dinh dang A, B hay C: "
		convert_invalid_Msg:
			.asciiz "Lua chon khong hop le (khong phai A, B hay C).\n"
		# luu chuoi moi theo cac dinh dang
		tmp_1: 
			.space 1024
		tmp_2: 
			.space 1024

	option3:
		.asciiz "3. Cho biet ngay vua nhap la thu may trong tuan\n"
	option4:
		.asciiz "4. Kiem tra nam trong chuoi TIME co phai la nam nhuan khong\n"

		is_LeapYear:
			.asciiz "La nam nhuan.\n"
		is_not_LeapYear:
			.asciiz "Khong la nam nhuan.\n"

	option5:
		.asciiz "5. Cho biet khoang thoi gian giua chuoi TIME_1 va TIME_2\n"
	option6:
		.asciiz "6. Cho biet 2 nam nhuan gan nhat voi nam trong chuoi TIME\n"


	# _____THAO TAC CAN THUC HIEN_____
	selectOption:
		.asciiz "Lua chon: "
	result: 	
		.asciiz "Ket qua: "
	invalidOptionMsg:
		.asciiz "Lua chon khong hop le. Moi chon lai.\n"
	askIfContinue:
		.asciiz "\nTiep tuc chuong trinh? (1: Co/ 0: Khong)\nLua chon: "


	# _____TEN THANG_____
	m_1:
		.asciiz "January"
	m_2:
		.asciiz "February"
	m_3:
		.asciiz "March"
	m_4:
		.asciiz "April"
	m_5:
		.asciiz "May"
	m_6:
		.asciiz "June"
	m_7:
		.asciiz "July"
	m_8:
		.asciiz "August"
	m_9:
		.asciiz "September"
	m_10:
		.asciiz "October"
	m_11:
		.asciiz "November"
	m_12:
		.asciiz "December"


	# _____TEN THU_____
	chu_nhat:
		.asciiz "Sunday"
	t_2:
		.asciiz "Monday"
	t_3:
		.asciiz "Tuesday"
	t_4:
		.asciiz "Wednesday"
	t_5:
		.asciiz "Thusday"
	t_6:
		.asciiz "Friday"
	t_7:
		.asciiz "Saturday"
	

	#______DU LIEU OUTPUT______
	outputMsg_CloserLeapYear:
		.asciiz "Hai nam nhuan (>= 1900) gan nhat la: "
	outputMsg_CloserLeapYear_and:
		.asciiz " and "
	outputMsg_GetTime:
		.asciiz "Khoang cach giua 2 khoang thoi gian (nam): "
	
.text:
#__________MENU & NHAP DU LIEU____________
main:	
	la $a0, TIME
	la $a1, inputString
	jal inputData #ham nhap du lieu
	slti $t0, $v1, 4
	beq $t0, 1, input_again 	#neu v1 < 4 -> ko hop le
	
	add $s0, $v0, $0 	#s0 luu TIME
	
	j printMenu
	
input_again: 
	la $a0, inputMsg_Invalid
	addi $v0, $0, 4  	
	syscall
	j main 		#yc nhap lai du lieu

printMenu:
	# xuat ra man hinh cac lua chon:
	addi $v0, $0, 4	

	la $a0, optionsMenu	
	syscall
	la $a0, option1	
	syscall
	la $a0, option2
	syscall
	la $a0, option3	
	syscall
	la $a0, option4
	syscall
	la $a0, option5
	syscall
	la $a0, option6	
	syscall
	j menuSelection

menuSelection:	
	la $a0, selectOption
	syscall
	addi $v0, $0, 8	
	la $a0, inputString	
	addi $a1, $0, 1024 	
	syscall

	jal isValidNumber
	beq $v0, 0, invalidOption
	jal toInt
	slti $t0, $v0, 1		#t0 = (v0 < 1)
	beq $t0, 1, invalidOption 	#v0 < 1
	slti $t0, $v0, 7
	bne $t0, 1, invalidOption	#v0 > 6
	add $a0, $v0, $0
	j solveOption

invalidOption:
	addi $v0, $0, 4
	la $a0, invalidOptionMsg
	syscall
	j menuSelection

solveOption:
	beq $a0, 1, solve_option1
	beq $a0, 2, solve_option2
	beq $a0, 3, solve_option3
	beq $a0, 4, solve_option4
	beq $a0, 5, solve_option5
	beq $a0, 6, solve_option6
	j endProgram

solve_option1:
	add $a0, $s0, $0
	addi $v0, $0, 4
	syscall
	j continueMenu

solve_option2:
	# lua chon dinh dang can xu ly (A,B hay C)
	addi $v0, $0, 4 # in chuoi lua chon
	la $a0, type_of_option2
	syscall

	addi $v0, $0, 8 
	la $a0, inputString	# doc chuoi ($a0 = type (A, B hay C))
	addi $a1, $0, 1024 
	syscall

	
	# chuyen con tro xuong dong moi de in ket qua
#	addi $a0, $0, 10 # (int)10 = (char)\n (ASCII)
#	addi $v0, $0, 11 # in ra ky tu
#	syscall

	# chuyen dinh dang
	add $a1, $0, $a0	#luu lua chon vao $a1
	add $a0, $0, $s0 	# $s0: TIME
	jal Convert

	beq $v1, 0, continueMenu 	#lua chon ko hop le -> ko chuyen doi dc

	# in ra dinh dang da duoc chuyen doi
	add $a0, $0, $s0
	addi $v0, $0, 4
	syscall
	j continueMenu

solve_option3:
	add $a0, $s0, $0
	jal WeekDay
	add $a0, $0, $v0
	addi $v0, $0, 4 # in chuoi option 3
	syscall
	j continueMenu

solve_option4:
	add $a0, $s0, $0
	jal LeapYear
	bne $v0, $0, solve_4_LeapYear
	la $a0, is_not_LeapYear
	addi $v0, $0, 4 # in ra chuoi ket qua
	syscall
	j continueMenu

	solve_4_LeapYear:
		la $a0, is_LeapYear
		addi $v0, $0, 4
		syscall
		j continueMenu

solve_option5:
#s1 luu chuoi TIME_2
	la $a0, inputMsg_time2
	addi $v0, $0, 4
	syscall

	la $a0, TIME_2
	la $a1, inputString
	jal inputData

	slti $t0, $v1, 4
	beq $t0, 1, input_again2 	#neu v1 < 4 -> ko hop le
	
	add $s1, $v0, $0 		#s1 luu TIME_2
	
	la $a0, outputMsg_GetTime
	addi $v0, $0, 4
	syscall

	#xu ly.....
	add $a0, $0, $s0
	add $a1, $0, $s1
	jal GetTime
	add $a0, $0, $v0	# Lay khoang cach luu vao $a0
	addi $v0, $0, 1	# syscall print int
	syscall

	j continueMenu
	
	input_again2: 
		la $a0, inputMsg_Invalid
		addi $v0, $0, 4  	
		syscall
		j solve_option5
		
solve_option6:
	#xu ly...
	la $a0, outputMsg_CloserLeapYear
	addi $v0, $0, 4	# syscall print string
	syscall

	add $a0, $0, $s0	# get TIME
	jal LeapYearCloser
	#jal Year
	add $a0, $0, $v0	# get nam nhuan 1
	addi $v0, $0, 1 	# syscall print int
	syscall

	la $a0, outputMsg_CloserLeapYear_and
	addi $v0, $0, 4 #syscall print string
	syscall

	add $a0, $0, $v1	# get nam nhuan 2
	addi $v0, $0, 1		# syscall print int
	syscall

	j continueMenu

continueMenu:
	la $a0, askIfContinue
	addi $v0, $0, 4
	syscall
	la $a0, inputString
	addi $a1, $0, 1024 	
	addi $v0, $0, 8
	syscall
	
	jal isValidNumber
	beq $v0, 0, invalidContinueOption
	jal toInt
	beq $v0, 0, endProgram		#ko tiep tuc -> thoat ctrinh
	beq $v0, 1, continueProgram	#tiep tuc
	j invalidContinueOption

invalidContinueOption:
	addi $v0, $0, 4
	la $a0, invalidOptionMsg
	syscall
	j continueMenu

continueProgram:
	la $a0, separateMsg
	addi $v0, $0, 4
	syscall
	j main

endProgram: 
	addi $v0, $0, 10
	syscall

#Ham nhap du lieu------------------------------------------------------------------
#OUTPUT: v0: (dia chi) chuoi TIME
#	 v1: tinh hop le
#	 v1 = hop le syntax (ngay, thang, nam) + hop le ngay
#	 v1 = 4: hop le; < 4: ko hop le
inputData: 
	addi $sp, $sp, -28
	sw $ra, 24($sp)
	sw $a0, 20($sp)
	sw $a1, 16($sp)

	add $v1, $0, $0	

	# Nhap ngay-------------------------------------------
	la $a0, inputMsg_day	#xuat msg ra man hinh
	addi $v0, $0, 4	
	syscall

	lw $a0, 16($sp)		#a0 = inputString
	addi $a1, $0, 1024	
	addi $v0, $0, 8	
	syscall			

	jal isValidNumber	
	add $v1, $v1, $v0 	

	lw $a0, 16($sp)		
	jal toInt		#chuyen ngay sang int
	sw $v0, 12($sp)		#luu ngay vao stack

	# Nhap thang------------------------------------------
	la $a0, inputMsg_month
	addi $v0, $0, 4	
	syscall
	
	lw $a0, 16($sp)		
	addi $a1, $0, 1024 	
	addi $v0, $0, 8	
	syscall
	
	jal isValidNumber 	
	add $v1, $v1, $v0	

	lw $a0, 16($sp)		
	jal toInt		#chuyen thang sang int
	sw $v0, 8($sp) 		#luu thang vao stack

	# Nhap nam--------------------------------------------
	la $a0, inputMsg_year
	addi $v0, $0, 4	
	syscall
	
	lw $a0, 16($sp) 	
	addi $a1, $0, 1024 	
	addi $v0, $0, 8 	
	syscall
	
	jal isValidNumber 	
	add $v1, $v1, $v0	

	lw $a0, 16($sp) 	
	jal toInt		#chuyen nam sang int
	sw $v0, 4($sp) 		#luu nam vao stack

	#syntax ko hop le -> return
	slti $t0, $v1, 4
	beq $t0, 0, inputDate_return

	#syntax hop le -> chuyen sang dang chuan DD/MM/YYYY
	lw $a0, 12($sp)		#ngay
	lw $a1, 8($sp)		#thang
	lw $a2, 4($sp) 		#nam
	lw $a3, 20($sp) 	#TIME
	
	sw $v1, 0($sp)
	jal ConvertToTIME

	lw $t0, 0($sp)
	add $v1, $v1, $t0
	j inputDate_return

inputDate_return:
	lw $ra, 24($sp)
	addi $sp, $sp, 28
	jr $ra

# _____SOLVE OPTION 1_____
#Ham tra ve chuoi ngay thang nam dang chuan----------------------------------------
#INPUT: a0,a1,a2: ngay thang nam (int)
#	a3: TIME
#	a0,a1,a2 bi thay doi gia tri trong ham
#OUTPUT: v0 = TIME dang chuan DD/MM/YYYY
#	 v1: tinh hop le (1: hop le, 0: ko hop le)
ConvertToTIME:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	jal isValidDate
	add $v1, $v0, $0
	beq $v1, 0, ConvertToTIME_return	#v1 = 0 -> ngay ko hop le -> return
	
	#Ngay hop le -> chuyen sang dang chuan-------------------------------------
	addi $t3, $0, 47		#t3 = 47 = '/'

	#a0 -> DD
	addi $t0, $0, 10
	div $a0, $t0			
	mflo $t1			#DAY / 10
	mfhi $a0			#DAY % 10
	#to char
	addi $t1, $t1, 48		
	addi $a0, $a0, 48		
	sb $t1, 0($a3)			#TIME[0]
	sb $a0, 1($a3)			#TIME[1]
	sb $t3, 2($a3)			#TIME[2] = '/'

	#a1 -> MM
	addi $t0, $0, 10
	div $a1, $t0
	mflo $t1			#MONTH / 10
	mfhi $a1			#MONTH % 10
	#to char
	addi $t1, $t1, 48		
	addi $a1, $a1, 48		
	sb $t1, 3($a3)			#TIME[3]
	sb $a1, 4($a3)			#TIME[4]
	sb $t3, 5($a3)			#TIME[5] = '/'

	#a2 -> YYYY
	addi $t0, $0, 1000
	div $a2, $t0
	mflo $t1			#t1 = YEAR / 1000
	mfhi $a2			#YEAR = YEAR % 1000
	addi $t1, $t1, 48		#to char
	sb $t1, 6($a3)			#TIME[6]

	addi $t0, $0, 100
	div $a2, $t0
	mflo $t1			#t2 = YEAR / 100
	mfhi $a2			#YEAR = YEAR % 100
	addi $t1, $t1, 48		#to char
	sb $t1, 7($a3)			#TIME[7]

	addi $t0, $0, 10
	div $a2, $t0
	mflo $t1			#t1 = YEAR / 10
	mfhi $a2			#YEAR = YEAR % 10
	addi $t1, $t1, 48		#to char
	addi $a2, $a2, 48		#to char
	sb $t1, 8($a3)			#TIME[8]
	sb $a2, 9($a3)			#TIME[9]
	sb $0, 10($a3)			#TIME[10] = '\0'
	
	ConvertToTIME_return:
		add $v0, $0, $a3	#v0 luu dia chi TIME
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
	
#Ham ktra syntax-------------------------------------------------------------------
#INPUT: a0: string, ko bi thay doi gia tri trong ham
#OUTPUT: v0 = 1 = hop le: chi chua cac ky tu chu so [0-9]
isValidNumber:
	add $t0, $0, $a0	#t0 = i
	addi $v0, $0, 1		
	
	isValidNumber_loop:
		lb $t1, 0($t0)				#t1 = p[i]
		
		addi $t2, $0, 10
		beq $t1, $t2, isValidNumber_return 	#p[i] = '\n' -> break
		beq $t1, $0, isValidNumber_return 	#p[i] = '\0' -> break
		
		slti $t2, $t1, 48			#48 = '0'
		bne $t2, $0, isValidNumber_false	#p[i] < '0' -> return false
		slti $t2, $t1, 58			#57 = '9'
		beq $t2, $0, isValidNumber_false	#p[i] > '9' -> return false
		
		addi $t0, $t0, 1			#i++
		j isValidNumber_loop
	
	isValidNumber_false:
		add $v0, $0, $0	# $v0 = 0, khong hop le
		j isValidNumber_return
	
	isValidNumber_return:
		jr $ra

#Ham ktra tinh hop le cua ngay-----------------------------------------------------
#INPUT: a0, a1, a2 > 0: ngay thang nam dang int 
#	ko bi thay doi gia tri trong ham
#OUTPUT: v0 = 1: hop le/ = 0: ko hop le
#Ham ktra tinh hop le cua ngay-----------------------------------------------------
#INPUT: a0, a1, a2 > 0: ngay thang nam dang int 
#	ko bi thay doi gia tri trong ham
#OUTPUT: v0 = 1: hop le/ = 0: ko hop le
isValidDate:
	addi $sp, $sp, -8
	sw $ra, 4($sp)
	
	add $v0, $0, $0			#mac dinh ko hop le
	#Thang > 12 || == 0 -> ko hop le
	slti $t0, $a1, 13		#t0 = (a1 < 13)
	beq $t0, 0, isValidDate_return 	#t0 = 0 -> a1 >= 13 -> return 
	beq $a1, 0, isValidDate_return	#a1 = 0 -> return

	#Ngay == 0 -> ko hop le
	beq $a0, 0, isValidDate_return

	#Nam < 1900 -> ko hop le
	slti $t0, $a2, 1900
	bne $t0, $0, isValidDate_return  

	#Nam > 9999 -> ko hop le
	slti $t0, $a2, 10000
	beq $t0, 0, isValidDate_return

	#Ktra ngay trong thang
	# - thang 1,3,5,7,8,10,12: ngay <= 31
	beq $a1, 1, checkLessThan31
	beq $a1, 3, checkLessThan31	
	beq $a1, 5, checkLessThan31
	beq $a1, 7, checkLessThan31	
	beq $a1, 8, checkLessThan31
	beq $a1, 10, checkLessThan31
	beq $a1, 12, checkLessThan31	

	# - thang 4,6,9,11: ngay <= 30
	beq $a1, 4, checkLessThan30
	beq $a1, 6, checkLessThan30
	beq $a1, 9, checkLessThan30
	beq $a1, 11, checkLessThan30

	# - thang 2
	beq $a1, 2, checkFebruary

	checkLessThan31:
		slti $t0, $a0, 32 		#t0 = (a0<32)
		beq $t0, 1, isValidDate_true	#t0=1 -> a0 <= 31
		j isValidDate_return

	checkLessThan30:
		slti $t0, $a0, 31 		#t0 = (a0<31)
		beq $t0, 1, isValidDate_true	#t0=1 -> a0 <= 30
		j isValidDate_return
	
	checkFebruary:
		beq $a0, 29, isLeapYear

		slti $t0, $a0, 30			
		beq $t0, 1, isValidDate_true	
		j isValidDate_return
	
	isLeapYear:
		sw $a0, 0($sp)
		add $a0, $0, $a2

		jal OnlyYear_LeapYear
		lw $a0, 0($sp)
		bne $v0, $0, isValidDate_true #if a0 is leap year goto isValidDate_true
		j isValidDate_return
	
	isValidDate_true:
		addi $v0, $0, 1

	isValidDate_return:
		lw $ra, 4($sp)
		addi $sp, $sp, 8
		jr $ra
	
#Ham chuyen tu chuoi -> int--------------------------------------------------------
#INPUT: a0 = chuoi mac dinh la hop le, ko bi thay doi gtri trong ham
#OUTPUT: v0 = int(a0)
toInt:
	add $v0, $0, $0			#v0 = res		
	add $t0, $0, $a0		#t0 = i	
toInt_loop:
	lb $t1, 0($t0)			#t1 = p[i]
	addi $t2, $0, 10
	beq $t1, $t2, toInt_return	#p[i] = '\n' -> return
	beq $t1, $0, toInt_return	#p[i] = '\0' -> return
	
	#res = res*10 + int(p[i])
	mult $v0, $t2
	mflo $v0			#res = res * 10
	addi $t1, $t1, -48		#p[i] to int
	add $v0, $v0, $t1		#res += p[i]
	
	add $t0, $t0, 1			#i++
	j toInt_loop
	
toInt_return:
	jr $ra


# _____SOLVE OPTION 2_____
Convert: 
#v0: kqua convert
#v1: true/ false
	lb $t1, 0($a1)
	
	addi $v1, $0, 1 	#gia dinh lua chon la hop le
	beq $t1, 65, convert_according_to_A
	beq $t1, 66, convert_according_to_B
	beq $t1, 67, convert_according_to_C

#	addi $t0, $0, 65 # 'A' ~ 65 (ASCII)
#	beq $a1, $t0, convert_according_to_A

#	addi $t0, $0, 66 # 'B' ~ 66 (ASCII)
#	beq $a1, $t0, convert_according_to_B

#	addi $t0, $0, 67 # 'C' ~ 67 (ASCII)
#	beq $a1, $t0, convert_according_to_C

	j Convert_invalid # xu ly truong hop dinh dang nhap vao khong phai A, B, C

	
convert_according_to_A: # Time: DD/MM/YYYY -> MM/DD/YYYY
	# lay DD va MM trong chuoi TIME ban dau
	# $ti ~ TIME[i]
	lb $t0, 0($a0)
	lb $t1, 1($a0)
	lb $t3, 3($a0)
	lb $t4, 4($a0)

	# dao vi tri cua DD va MM
	# DD <-> MM 
	sb $t3, 0($a0)
	sb $t4, 1($a0)
	sb $t0, 3($a0)
	sb $t1, 4($a0)
	j Convert_exit

convert_according_to_B: # Time: DD/MM/YYYY -> Month DD, YYYY
	# luu vao stack
	addi $sp, $sp, -24
	sw $ra, 20($sp)
	sw $a0, 16($sp) # chuoi TIME dang chuan
	sw $a1, 12($sp) # chuoi TIME chuyen theo dinh dang

	# lay thang trong chuoi (int)
	jal Month
	add $a0, $0, $v0

	# chuyen thang thanh ten (vi du: 1 -> January,..., 12 -> December)
	jal NameOfMonth
	sw $v0, 8($sp) # $v0 luu lai ten thang

	# xu ly DD -> dua vao chuoi tmp_1: ' DD, '
	lw $a0, 16($sp) # $a0 = TIME
	la $t0, tmp_1

	addi $t1, $0, 32  # 32 = ' ' (ASCII)
	sb $t1, 0($t0) # tmp_1[0] = $t1 = ' '

	lb $t1, 0($a0) # $t1 = TIME[0]
	sb $t1, 1($t0) # tmp_1[1] = $t1 = TIME[0]
	
	lb $t1, 1($a0) # $t1 = TIME[1]
	sb $t1, 2($t0) # tmp_1[2] = $t1 = TIME[1]

	sw $t0, 4($sp) # luu tmp_1

	# xu ly YYYY -> dua tiep vao chuoi tmp_2: ', YYYY'
	la $t0, tmp_2
	
	addi $t1, $0, 44 # 44 = ',' (ASCII)
	sb $t1, 0($t0) # tmp_2[0] = ','

	addi $t1, $0, 32  # 32 = ' ' (ASCII)
	sb $t1, 1($t0) # tmp_2[1] = $t1 = ' '

	lb $t1, 6($a0) # $t1 = TIME[6]
	sb $t1, 2($t0) # tmp_2[2] = $t1 = TIME[6]
	
	lb $t1, 7($a0) # $t1 = TIME[7]
	sb $t1, 3($t0) # tmp_2[3] = $t1 = TIME[7]
	
	lb $t1, 8($a0) # $t1 = TIME[8]
	sb $t1, 4($t0) # tmp_2[4] = $t1 = TIME[8]

	lb $t1, 9($a0) # $t1 = TIME[9]
	sb $t1, 5($t0) # tmp_2[5] = $t1 = TIME[9]

	sb $0, 6($t0)

	sw $t0, 0($sp) # luu tmp_2

	# Noi chuoi -> Month DD, YYYY
	lw $a1, 8($sp) # chep chuoi NameOfMonth vao $a1 ~ TIME
	jal strcpy

	lw $a1, 4($sp)
	jal strcat # Noi chuoi ' DD' vao TIME

	lw $a1, 0($sp)
	jal strcat # Noi chuoi ', YYYY' vao TIME

	# khoi phuc lai stack
	lw $ra, 20($sp)
	lw $a0, 16($sp)
	lw $a1, 12($sp)
	addi $sp, $sp, 24

	j Convert_exit

convert_according_to_C: # Time: DD/MM/YYYY -> DD Month, YYYY
	# luu vao stack
	addi $sp, $sp, -24
	sw $ra, 20($sp)
	sw $a0, 16($sp) # chuoi TIME dang chuan
	sw $a1, 12($sp) # chuoi TIME chuyen theo dinh dang

	# lay thang trong chuoi (int)
	jal Month
	add $a0, $0, $v0

	# chuyen thang thanh ten (vi du: 1 -> January,..., 12 -> December)
	jal NameOfMonth
	sw $v0, 8($sp) # $v0 luu lai ten thang

	# xu ly DD -> dua vao chuoi tmp_1: 'DD '
	lw $a0, 16($sp) # $a0 = TIME
	la $t0, tmp_1

	lb $t1, 0($a0) # $t1 = TIME[0]
	sb $t1, 0($t0) # tmp_1[0] = $t1 = TIME[0]
	
	lb $t1, 1($a0) # $t1 = TIME[1]
	sb $t1, 1($t0) # tmp_1[1] = $t1 = TIME[1]
	
	addi $t1, $0, 32  # 32 = ' ' (ASCII)
	sb $t1, 2($t0) # tmp_1[2] = $t1 = ' '
	
	sw $t0, 4($sp) #luu tmp_1

	# xu ly YYYY -> dua vao chuoi tmp_2: ', YYYY'
	la $t0, tmp_2

	addi $t1, $0, 44 # 44 = ',' (ASCII)
	sb $t1, 0($t0) # tmp_2[0] = $t1 = ','	

	addi $t1, $0, 32 # 32 = ' ' (ASCII)
	sb $t1, 1($t0) # tmp_2[1] = $t1 = ' '

	lb $t1, 6($a0) # $t1 = TIME[6]
	sb $t1, 2($t0) # tmp_2[2] = $t1 = TIME[6]
	
	lb $t1, 7($a0) # $t1 = TIME[7]
	sb $t1, 3($t0) # tmp_2[3] = $t1 = TIME[7]
	
	lb $t1, 8($a0) # $t1 = TIME[8]
	sb $t1, 4($t0) # tmp_2[4] = $t1 = TIME[8]

	lb $t1, 9($a0) # $t1 = TIME[9]
	sb $t1, 5($t0) # tmp_2[5] = $t1 = TIME[9]
	
	sw $t0, 0($sp) # luu tmp_2

	# Noi chuoi -> DD Month, YYYY
	lw $a1, 4($sp) # chep chuoi tmp_1 = 'DD ' vao $a1 ~ TIME
	jal strcpy

	lw $a1, 8($sp)
	jal strcat # Noi chuoi NamOfMonth vao $a1

	lw $a1, 0($sp) 
	jal strcat # noi chuoi tmp_2 = ', YYYY' vao $a1

	# khoi phuc lai stack
	lw $ra, 20($sp)
	lw $a0, 16($sp)
	lw $a1, 12($sp)
	addi $sp, $sp, 24

	j Convert_exit

Convert_invalid:
	addi $v1, $0, 0 	#lua chon ko hop le
	addi $v0, $0, 4
	la $a0, convert_invalid_Msg
	syscall
	j Convert_exit

Convert_exit:
	add $v0, $0, $a0
	jr $ra	

strcpy:
	# save to stack
	addi $sp, $sp, -4
	sw $s0, 0($sp)
	add $s0, $0, $0 		# i = 0
strcpy_loop:
	add $t0, $s0, $a1		# $t0 = &y[i]
	lb $t1, 0($t0) 			# $t1 = y[i]
	add $t2, $s0, $a0 		# $t2 = &x[i]
	sb $t1, 0($t2) 			# x[i] = y[i]
	beq $t1, $0, strcpy_exit	# Neu x[i] == '\0'
	addi $s0, $s0, 1		# i += 1
	j strcpy_loop
strcpy_exit:
	# restore from stack
	lw $s0, 0($sp)
	addi $sp, $sp, 4
	jr $ra

# Ham noi chuoi
strcat:
	# save to stack
	addi $sp, $sp, -8
	sw $s0, 0($sp)
	sw $s1, 4($sp)

	add $s0, $0, $0		# $s0 la i = 0
	add $s1, $0, $0 		# $s1 la j = 0
strcat_findEndLoop:
	add $t3, $a0, $s0
	lb $t4, 0($t3) 			# $t4 = x[i]
	beq $t4, $0, appendLoop	# neu x[i] == '\0'
	addi $s0, $s0, 1  		# i += 1
	j strcat_findEndLoop
appendLoop:
	add $t4, $a1, $s1 		# $t4 = &y[j]
	lb $t5, 0($t4) 			# $t5 = y[j]
	add $t3, $a0, $s0 		# $t3 = &x[i]
	sb $t5, 0($t3) 			# x[i] = y[j]
	beq $t5, $0, strcat_exit	# neu x[i] == '\0'
	addi $s0, $s0, 1		# i += 1
	addi $s1, $s1, 1		# j += 1
	j appendLoop
strcat_exit:
	# restore from stack
	lw $s0, 0($sp)
	lw $s1, 4($sp)
	addi $sp, $sp, 8
	jr $ra


# $a0: luu chuoi TIME
# $v0: tra ve ket qua kieu int tuong ung cho tung ham (Day, Month, Year)
Day: # DD trong chuoi TIME -> (int)DD
	# luu vao stack
	# $t0 ~ TIME[0], $t1 ~ TIME[1]
	addi 	$sp, $sp, -8
	sw	$ra, 4($sp)
	sw	$a0, 0($sp)

	# xu ly hang chuc cua ngay
	lb	$t0, 0($a0)
	addi	$t0, $t0, -48 # chuyen tu char sang int (ASCII)
	
	li	$t1, 10
	mult	$t0, $t1
	mflo	$t0
	
	# xu ly hang don vi cua ngay 
	lb	$t1, 1($a0)
	addi	$t1, $t1, -48
	add	$t0, $t0, $t1

	add 	$v0, $0, $t0

	# khoi phuc lai stack
	lw	$ra, 4($sp)
	lw	$a0, 0($sp)
	addi 	$sp, $sp, 8
	
	jr	$ra

Month: # MM trong chuoi TIME -> (int)MM
	# luu vao stack
	# $t0 ~ TIME[3], $t1 ~ TIME[4]
	addi 	$sp, $sp, -8
	sw	$ra, 4($sp)
	sw	$a0, 0($sp)

	# xu ly hang chuc cua thang
	lb	$t0, 3($a0)
	addi	$t0, $t0, -48
	
	li	$t1, 10
	mult	$t0, $t1
	mflo	$t0
	
	# xu ly hang don vi cua thang
	lb 	$t1, 4($a0)
	addi	$t1, $t1, -48
	add	$t0, $t0, $t1

	add 	$v0, $0, $t0

	# khoi phuc lai stack
	lw	$ra, 4($sp)
	lw	$a0, 0($sp)
	addi 	$sp, $sp, 8
	
	jr	$ra

Year:
	# luu vao stack
	addi $sp, $sp, -12
	sw $ra, 8($sp)
	sw $a0, 4($sp)

	# xu ly hang nghin va tram cua nam
	la	$a0, 6($a0) # nam trong chuoi TIME bat dau tu TIME[6]
	jal	Day
	
	li	$t1, 100
	mult	$v0, $t1
	mflo	$t0
	sw 	$t0, 0($sp)

	# xu ly hang chuc va don vi cua nam
	lw 	$a0, 4($sp)
	la	$a0, 8($a0)
	jal	Day

	# luu ket qua vao $v0
	lw	$t0, 0($sp)
	add 	$v0, $v0, $t0

	# khoi phuc stack
	lw	$ra, 8($sp)
	lw	$a0, 4($sp)
	addi 	$sp, $sp, 12
	
	jr	$ra

# Ham tra ve ten cua thang (thang 1 -> January, ...)
# $a0 : month(int), $v0: month(string)
NameOfMonth:
	beq $a0, 1, Jan
	beq $a0, 2, Feb
	beq $a0, 3, Mar
	beq $a0, 4, Apr
	beq $a0, 5, May
	beq $a0, 6, Jun
	beq $a0, 7, Jul
	beq $a0, 8, Aug
	beq $a0, 9, Sep
	beq $a0, 10, Oct
	beq $a0, 11, Nov

	j Dec	


	Jan:
		la $v0, m_1
		jr $ra
	Feb:
		la $v0, m_2
		jr $ra
	Mar:
		la $v0, m_3
		jr $ra
	Apr:
		la $v0, m_4
		jr $ra
	May:
		la $v0, m_5
		jr $ra
	Jun:
		la $v0, m_6
		jr $ra
	Jul:
		la $v0, m_7
		jr $ra
	Aug:
		la $v0, m_8
		jr $ra
	Sep:
		la $v0, m_9
		jr $ra
	Oct:
		la $v0, m_10
		jr $ra
	Nov:
		la $v0, m_11
		jr $ra
	Dec:
		la $v0, m_12
		jr $ra
		

# _____SOLVE OPTION 3_____
WeekDay:
	# save to stack
	addi $sp, $sp, -24
	sw $ra, 20($sp)
	sw $a0, 16($sp) # TIME
	sw $a1, 12($sp) # luu ngay
	sw $a2, 8($sp) # luu thang
	sw $a3, 4($sp) # luu nam
	sw $s0, 0($sp) # ket qua tra ve

	lw	$a0, 16($sp)
	jal	Day
	move	$a1, $v0
	
	lw	$a0, 16($sp)
	jal	Month
	move	$a2, $v0

	lw	$a0, 16($sp)
	jal	Year
	move	$a3, $v0

	li	$t3, 3
	slt	$t3, $a2, $t3
	beq	$t3, $0, cong_thuc
	addi	$a2, $a2, 12
	addi	$a3, $a3, -1
	j 	cong_thuc
	
cong_thuc: # thu_trong_tuan = (ngay + 2*thang + (3*(thang + 1)) div 5 + nam + (nam div 4)) mod 7
	add $s0, $0, $a1

	addi $t4, $0, 2 # $t4 = 2
	mult $a2, $t4 # thang*2
	mflo $a1 # $a1 = thang*2

	add $s0, $s0, $a1 # $s0 = ngay + 2*thang

	addi $a2, $a2, 1 # thang + 1
	addi $t4, $0, 3 # $t4 = 3
	mult $a2, $t4
	mflo $a2 # $t1 = 3*(thang + 1)

	addi $t4, $0, 5 # $t4 = 5
	div $a2, $t4 # 3*(thang + 1) div 5
	mflo $a2 # $a2 = 3*(thang + 1) div 5

	add $s0, $s0, $a2 # $s0 = ngay + 2*thang + (3*(thang + 1) div 5)
	
	add $s0, $s0, $a3 # $s0 = ngay + 2*thang + (3*(thang + 1) div 5) + nam

	addi $t4, $0, 4 # $t4 = 4
	div $a3, $t4
	mflo $a3 # $t2 = nam div 4

	add $s0, $s0, $a3 # $s0 = ngay + 2*thang + (3*(thang + 1) div 5) + nam + (nam div 4)

	addi $t4, $0, 7
	div $s0, $t4
	mfhi $s0 # $s0 = (ngay + 2*thang + (3*(thang + 1)) div 5 + nam + (nam div 4)) mod 7
	
	beq $s0, 0, Sun
	beq $s0, 1, Mon
	beq $s0, 2, Tue
	beq $s0, 3, Wed
	beq $s0, 4, Thu
	beq $s0, 5, Fri
	j Sat

	Sun:
		la $v0, chu_nhat
		j restone_stack
	Mon:
		la $v0, t_2
		j restone_stack
	Tue:
		la $v0, t_3
		j restone_stack
	Wed:
		la $v0, t_4 
		j restone_stack
	Thu:
		la $v0, t_5 
		j restone_stack
	Fri:
		la $v0, t_6 
		j restone_stack
	Sat: 
		la $v0, t_7 
		j restone_stack
restone_stack:
	lw $ra, 20($sp)
	lw $a0, 16($sp)
	lw $a1, 12($sp)
	lw $a2, 8($sp)
	lw $a3, 4($sp)
	lw $s0, 0($sp)
	addi $sp, $sp, 24
	jr $ra

# _____SOLVE OPTION 4_____
# $a0: TIME
# $v0: gia tri tra ve (1_ nam nhuan, 0_ khong phai nam nhuan)
LeapYear: # $a0: YEAR
	# luu bien vao stack
	addi $sp, $sp, -8
	sw $ra, 4($sp)
	sw $a0, 0($sp)

	jal Year # tach nam
	add $a0, $0, $v0

	jal OnlyYear_LeapYear #ham kiem tra n?m nhuan $v0 = 1 (nam nhuan)
	
	# lay lai dia chi quay ve
	lw $ra, 4($sp)
	lw $a0, 0($sp)
	addi $sp, $sp, 8 # ket thuc viec dung stack
	jr $ra 



#______________SOLVE OPTION 5______________________
#Ham cho biet thoi gian  giua chuoi TIME_1 va TIME_2
#INPUT: a0, a1: 2 chuoi thoi gian can tinh khoang cach TIME_1, TIME_2
#OUTPUT: v0 (int) = khoang cach thoi gian (nam)
GetTime:
	# save into stack
	addi $sp, $sp, -12
	
	sw $ra, 8($sp)
	sw $a0, 4($sp)
	sw $a1, 0($sp)

	jal CompareTime

	# TIME_1 == TIME_2 => distance_year = 0
	beq $v0, $0, GetTime_return

	# TIME_1 > TIME_2 => v0 == 1
	slt $t0, $v0, $0 # v0 < 0
	bne $t0, $0, GetTime_skip # if true goto GetTime_skip

	jal SubYear
	j GetTime_return

GetTime_skip:
	# TIME_1 < TIME_2 => v0 == -1
	lw $a0, 0($sp)
	lw $a1, 4($sp)

	jal SubYear

GetTime_return:
	lw $ra, 8($sp)
	lw $a0, 4($sp)
	lw $a1, 0($sp)
	addi $sp, $sp, 12
	
	jr $ra

#Ham so sanh chuoi TIME
#INPUT: a0, a1: 2 chuoi thoi gian can tinh khoang cach TIME_1, TIME_2
#OUTPUT: v0 = 1: TIME_1 > TIME_2, v0 = 0: TIME_1 = TIME_2, v0 = -1: TIME_1 < TIME_2
CompareTime:
	# save into stack
	addi $sp, $sp, -36
	sw $ra, 32($sp)
	sw $a0, 28($sp)
	sw $a1, 24($sp)

	# save TIME_1
	jal Year
	sw $v0, 20($sp)		# save Year(TIME_1)
	jal Month
	sw $v0, 16($sp)		# save Month(TIME_1)
	jal Day
	sw $v0, 12($sp)		# save Day(TIME_1)

	# save TIME_2
	lw $a0, 24($sp)		# get TIME_2
	jal Year
	sw $v0, 8($sp)		# save Year(TIME_2)
	jal Month
	sw $v0, 4($sp)		# save Month(TIME_2)
	jal Day
	sw $v0, 0($sp)		# save Day(TIME_2)

Compare_year:
	lw $t0, 20($sp) # t0 = Year(TIME_1)
	lw $t1, 8($sp)  # t1 = Year(TIME_2)
	
        beq $t0, $t1, Compare_month

	slt $t3, $t0, $t1 # t0 < t1
	bne $t3, $0, Compare_Smaller #if Year(TIME_1) < Year(TIME_2) goto Compare_Smaller
	
	j Compare_Bigger #if Year(TIME_1) != Year(TIME_2) goto Compare_Bigger
Compare_month:
	lw $t0, 16($sp) # t0 = Month(TIME_1)
	lw $t1, 4($sp)  # t1 = Month(TIME_2)
	
	beq $t0, $t1, Compare_day

	slt $t3, $t0, $t1 # t0 < t1
	bne $t3, $0, Compare_Smaller #if Month(TIME_1) < Month(TIME_2) goto Compare_Smaller
	
	j Compare_Bigger #if Month(TIME_1) != Month(TIME_2) goto Compare_Bigger
Compare_day:
	lw $t0, 12($sp) # t0 = Day(TIME_1)
	lw $t1, 0($sp)  # t1 = Day(TIME_2)
	
	beq $t0, $t1, Compare_Equal

	slt $t3, $t0, $t1 # t0 < t1
	bne $t3, $0, Compare_Smaller #if Day(TIME_1) < Day(TIME_2) goto Compare_Smaller
	
	j Compare_Bigger #if Day(TIME_1) != Day(TIME_2) goto Compare_Bigger
Compare_Smaller:
	addi $v0, $0, -1 # v0 = -1
	j CompareTime_return
Compare_Bigger:
	addi $v0, $0, 1 # v0 = 1
	j CompareTime_return
Compare_Equal:
	add $v0, $0, $0
CompareTime_return:
	# restore from stack
	lw $ra, 32($sp)
	lw $a0, 28($sp)
	lw $a1, 24($sp)
	addi $sp, $sp, 36

	jr $ra
	
#Ham tinh khoang cach nam giua 2 chuoi TIME
#INPUT: a0: TIME_1, a1:TIME_2 and a0 > a1
#OUPUT: v0 (int): distance_year
SubYear:
	# save into stack
	addi $sp, $sp, -36
	sw $ra, 32($sp)
	sw $a0, 28($sp)
	sw $a1, 24($sp)

	# save TIME_1
	jal Year
	sw $v0, 20($sp)		# save Year(TIME_1)
	jal Month
	sw $v0, 16($sp)		# save Month(TIME_1)
	jal Day
	sw $v0, 12($sp)		# save Day(TIME_1)

	# save TIME_2
	lw $a0, 24($sp)		# get TIME_2
	jal Year
	sw $v0, 8($sp)		# save Year(TIME_2)
	jal Month
	sw $v0, 4($sp)		# save Month(TIME_2)
	jal Day
	sw $v0, 0($sp)		# save Day(TIME_2)

	add $v0, $0, $0 # v0 = 0

	lw $t0, 20($sp) # t0 = Year(TIME_1)
	lw $t1, 8($sp)  # t1 = Year(TIME_2)
	beq $t0, $t1, SubYear_return # if Year(TIME_1) == Year(TIME_2) goto SubYear_return

	add $v0, $v0, $t0 # v0 = t0
	sub $v0, $v0, $t1 # v0 = t0 - t1
SubYear_Compare_month:
	lw $t0, 16($sp) # t0 = Month(TIME_1)
	lw $t1, 4($sp)  # t1 = Month(TIME_2)

	beq $t0, $t1, SubYear_day #if Month(TIME_1) == Month(TIME_2) goto SubYear_day
	
	slt $t3, $t1, $t0 # t1 < t0
	bne $t3, $0, SubYear_return #if Month(TIME_2) < Month(TIME_1) goto SubYear_return
	
	j SubYear_skip #if Month(TIME_1) < Month(TIME_2) goto SubYear_skip
SubYear_day:
	lw $t0, 12($sp) # t0 = Day(TIME_1)
	lw $t1, 0($sp)  # t1 = Day(TIME_2)

	beq $t0, $t1, SubYear_return #if Day(TIME_1) == Day(TIME_2) goto SubYear_return
	
	slt $t3, $t1, $t0 # t1 < t0
	bne $t3, $0, SubYear_return #if Day(TIME_2) < Day(TIME_1) goto SubYear_return
	
	#else Day(TIME_1) < Day(TIME_2)
SubYear_skip:
	addi $v0, $v0, -1
SubYear_return:
	# restore from stack
	lw $ra, 32($sp)
	lw $a0, 28($sp)
	lw $a1, 24($sp)
	addi $sp, $sp, 36

	jr $ra

#____________SOLVE OPTION 6________________
# Ham tim hai nam nhuan gan nhat
#INPUT: a0: TIME
#OUTPUT: v0: nam nhuan 1, v1: nam nhuan 2
LeapYearCloser:
	# save into stack
	addi $sp, $sp, -8
	sw $ra, 4($sp)
	sw $a0, 0($sp)

	jal Year

	add $t0, $v0, $0 	#t0 = year
	addi $t1, $0, 1 	#t1 save distance from year to year_next
	addi $t2, $0, 1		#t2 save distance from year to year_past
	
	addi $t3, $0, 1900 	#dk xet year >= t3

LeapYearCloser_Next:
	add $a0, $t0, $t1	# get year + t1
	jal OnlyYear_LeapYear
	bne $v0, $0, LeapYearCloser_Past #if a0 is leap year goto LeapYearCloser_Past

	addi $t1, $t1, 1	# t1 += 1
	j LeapYearCloser_Next

LeapYearCloser_Past:
	sub $a0, $t0, $t2	# get year - t2
	
	slt $t4, $a0, $t3 # a0 < t0
	bne $t4, $0, LeapYearCloser_Next_Next # if true then goto LeapYearCloser_Next_Next

	jal OnlyYear_LeapYear
	bne $v0, $0, LeapYearCloser_Check #if a0 is leap year goto LeapYearCloser_Check

	addi $t2, $t2, 1	# t2 += 1
	j LeapYearCloser_Past

LeapYearCloser_Check:
	LeapYearCloser_Check_next:
	addi $t4, $t1, 4	# t4 save distance from year to year_next_next
	add $a0, $t0, $t4
	jal OnlyYear_LeapYear
	bne $v0, $0, LeapYearCloser_Check_past
	
	addi $t4, $t4, 4
	
	LeapYearCloser_Check_past:
	addi $t5, $t2, 4	# t5 save distance from year to year_past_past
	sub $a0, $t0, $t5
	jal OnlyYear_LeapYear
	bne $v0, $0, LeapYearCloser_Check_return
	
	addi $t5, $t5, 4

	LeapYearCloser_Check_return:
	add $a0, $t1, $t2 # distance(year_past, year_next)
	add $a1, $0, $t4  # distance(year, year_next_next)
	add $a2, $0, $t5  # distance(year, year_past_past)

	jal Min
	beq $v0, 0, Return_past_next
	beq $v0, 1, Return_next_next
	beq $v0, 2, Return_past_past

	Return_past_next:
	add $v1, $t0, $t1
	sub $v0, $t0, $t2
	j LeapYearCloser_return
	
	Return_past_past:
	sub $v0, $t0, $t5
	sub $v1, $t0, $t2
	j LeapYearCloser_return

	Return_next_next:
	add $v0, $t0, $t1
	add $v1, $t0, $t4
	j LeapYearCloser_return

LeapYearCloser_Next_Next:
	add $v0, $t0, $t1

	addi $v1, $v0, 4 # i+= 4 (perhaps Leap Year)
	add $a0, $0, $v1
	jal OnlyYear_LeapYear
	bne $v0, $0, LeapYearCloser_Next_Next_return

	addi $v1, $v1, 4 # i+= 8 (sure)
	
	LeapYearCloser_Next_Next_return:
		add $v0, $t0, $t1

LeapYearCloser_return:
	# restore from stack
	lw $ra, 4($sp)
	lw $a0, 0($sp)
	addi $sp, $sp, 8
	
	jr $ra

# Ham kiem tra nam nhuan
#INPUT: a0: year
#OUTPUT: 1: leap year, 0: not leap year
OnlyYear_LeapYear:
	#save into stack
	addi $sp, $sp, -8
	sw $t1, 4($sp)
	sw $t2, 0($sp)
	
	addi $t1, $0, 400 # t1 = 400
	div $a0, $t1
	mfhi $t2 				# t2 = year % 400
	beq $t2, $0, OnlyYear_True	# if year % 400 == 0

	addi $t1, $0, 4 # t1 = 4
	div $a0, $t1
	mfhi $t2 				# t2 = year % 4
	bne $t2, $0, OnlyYear_False # if year % 4 != 0

	addi $t1, $0, 100 # t1 = 100
	div $a0, $t1
	mfhi $t2 				# t2 = year % 100
	beq $t2, $0, OnlyYear_False # if year % 4 == 0 and year % 100 == 0
OnlyYear_True:
	addi $v0, $0, 1		
	j OnlyYear_return
OnlyYear_False:
	add $v0, $0, $0
OnlyYear_return:
	lw $t1, 4($sp)
	lw $t2, 0($sp)

	addi $sp, $sp, 8

	jr $ra

#INPUT: a0: year_past -> year_next, a1:year -> year_next_next, a2: year_past_past -> year
#OUTPUT: 0, 1, 2 t??ng ?ng v?i a0, a1, a2 trong do ai nho nhat
Min:
	#save into stack
	addi $sp, $sp, -4
	sw $t0, 0($sp)

	slt $t0, $a1, $a0 #if a1 < a0
	beq $t0, $0, Min_check #false (a0 <= a1) goto Min_check
	#else a1 < a0
	slt $t0, $a2, $a1 #if a2 < a1
	beq $t0, $0, Min_1 #false (a1 <= a2) goto Min_1
	#else a2 < a1
	j Min_2
Min_check:
	slt $t0, $a2, $a0 #if a2 < a0
	beq $t0, $0, Min_0 #false (a0 <= a2) goto Min_0
	#if a0 > a2
	j Min_2
Min_1:
	addi $v0, $0, 1
	j Min_return
Min_0:
	add $v0, $0, $0
	j Min_return
Min_2:
	addi $v0, $0, 2
Min_return:
	lw $t0, 0($sp)
	addi $sp, $sp, 4

	jr $ra