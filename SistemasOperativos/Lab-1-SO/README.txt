INTEGRANTES:
	Nombre: Jonathan Olivares, rol: 202073096-2
	Nombre: Sebastián Arrieta, rol: 202173511-9
	
INSTRUCCIONES:

Se tienen 2 códigos ".c" uno dice main que es el código sin optimizar y otro dice mainOpti que es el código optimizado. Además se encuentra el informe.
	
Para ejecutar el código se debe hacer uso del makefile, con el comando make se crearán las carpetas correspondientes y los ejecutables correspondientes.

Los archivos de texto que contienen las sopas de letras deben estas en la carpeta "archivos" para que el programa pueda procesarlos.

Se crearán 2 ejecutables estos son:

-main
-mainOpti

Para correr el programa basta con el comando "make run" (para ejecutar el código sin optimizar) y "make runOpti" ( para ejecutar el código optimizado) sin comillas.

Para eliminar los 2 archivos ejecutables correspondientes basta con make clean.

SUPUESTOS:

Se asume que la orientación del txt siempre será en minuscula, ej: horizontal.
Tambien se asume que cada letra del txt tendrá el mismo formato, la de letra en mayuscula y luego espacio hasta el final de la linea que contendra un salto de linea "\n", asi
hasta llegar a la ultima letra de la sopa a la que le seguira el EOF(End of file) correspondiente.
