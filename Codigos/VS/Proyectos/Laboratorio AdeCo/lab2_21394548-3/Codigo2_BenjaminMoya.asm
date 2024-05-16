.data
	rspace1: .space 4  
	rspace2: .space 4
	msg1: .asciiz "Introduzca las coordenadas del primer vector:\n"
	msg2: .asciiz "Introduzca las coordenadas del segundo vector:\n"
	msgx: .asciiz "X:"
	msgy: .asciiz "Y:"
	msgz: .asciiz "Z:"
	result: .asciiz "La coordenada es: "
	x: .float 0.0  
	y: .float 0.0
	z: .float 0.0
	set1: .float 2.0   
	set2: .float 10.0   
	set3: .float 0.0
.text
	main:
  			
  		jal GetFirstVector
  		jal GetSecondVector
  		jal Euclud

  		lw $ra, 0($sp)
  		addiu $sp, $sp, 4

  					# Mostramos el resultadoo
  		li $v0, 4
  		la $a0, result
  		syscall
  		li $v0, 2
  		mov.s $f12, $f12
  		syscall
  					#Llamamos al termino de la ejecucion
  		jal End

#------------------------------------Subrutinas-----------------------------------#

	GetFirstVector:
					#Pedimos las coordenadas del primer vector por consola y los guardamos en los registros del coproceasador
  		li $v0, 4
  		la $a0, msg1
  		syscall
  		li $v0, 4
  		la $a0, msgx
  		syscall	
  		li $v0, 6
  		syscall
  		swc1 $f0, x
  		li $v0, 4
  		la $a0, msgy
  		syscall
  		li $v0, 6
  		syscall
  		swc1 $f0, y
  		li $v0, 4
  		la $a0, msgz
  		syscall
  		li $v0, 6
  		syscall
  		swc1 $f0, z
  		
  		lwc1 $f12, x
  		lwc1 $f13, y
  		lwc1 $f14, z
 
  		jr $ra
  
	GetSecondVector:
					#Pedimos las coordenadas del segundo vector por consola y los guardamos en los registros del coproceasador
  		li $v0, 4
  		la $a0, msg2
  		syscall
  		li $v0, 4
  		la $a0, msgx
  		syscall
  		li $v0, 6
  		syscall
  		swc1 $f0, x
  		li $v0, 4
  		la $a0, msgy
  		syscall
  		li $v0, 6
  		syscall
  		swc1 $f0, y
  		li $v0, 4
  		la $a0, msgz
  		syscall
  		li $v0, 6
  		syscall
  		swc1 $f0, z

  		lwc1 $f4, x
  		lwc1 $f5, y
  		lwc1 $f6, z

  		jr $ra

	Euclud:
  					#Determinamos el cuadrado de las diferencias de ccada coordenada
  		sub.s $f3, $f4, $f12
  		mul.s $f3, $f3, $f3
		sub.s $f4, $f5, $f13
  		mul.s $f4, $f4, $f4
  		sub.s $f5, $f6, $f14
  		mul.s $f5, $f5, $f5
  		add.s $f6, $f3, $f4
  		add.s $f6, $f6, $f5
  		
 		mov.s $f0 , $f6
					#Aproximamos la raiz mediante el metodo de Newton-Raphson
		aproxsquare:
    			lwc1 $f5, set1
    			lwc1 $f1, set2
    			lwc1 $f6, set3

    					
		newton:
    					# Calculamos una aproximacion inicial para luego comparala con la anterior reiniciando el bucle mientras el anterior con el actual no sean iguales
    			div.s $f2, $f0, $f1
    			add.s $f3, $f2, $f1   
    			div.s $f3, $f3, $f5   

    					
    			c.eq.s $f3, $f1
    			bc1t finalstep  
    			mov.s $f1, $f3
    			
    			j newton

		finalstep:
    					#Dejamos el resultado en el registro de retorno para flotantes
   			mov.s $f12, $f3      
    			jr $ra              
    
	End:
		li $v0,10
		syscall
	
 


  
