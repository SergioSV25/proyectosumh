<?php
include "seguridad.php";
echo"<a href=cerrar_sesion.php>Cerrar sesion</a><br><a href=index.php>Inicio</a>";
?>
<html>
<body>
	<form method=post action="insert_repuesto2.php" enctype="multipart/form-data">
		Referencia:
		<input type=text name=referencia>
		<br>Descripcion:
		<input type=text name=descrip>
		<br>Importe(€):
		<input type=text name=imp>
		<br>Ganancia(%):
		<input type=text name=ganancia>

		
		<br><input type=submit value="Introducir Repuesto">
		<br><input type=reset value="Borrar">
	</form>
</body>
</html>