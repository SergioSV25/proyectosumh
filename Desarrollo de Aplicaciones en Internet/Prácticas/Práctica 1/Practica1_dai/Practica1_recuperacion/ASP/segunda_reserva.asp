<!--- #include file=conexion.asp -->
<!DOCTYPE html>
<html>
	<body>
	
	
		<%
           Set maxid = Conexion.execute("select max(IDRESERVA) as ultimo_id from RESERVA")
			id_reserva = maxid("ultimo_id") + 1
			
			idreserva  = request.querystring("idreserva")
			id_vuelo  = request.querystring("idvuelo")
			
			
			set reserva = Conexion.Execute("select * from RESERVA where IDRESERVA="& idreserva)
			
			nombre = reserva("NOMBRE")
			apellidos = reserva("APELLIDOS")
			n_asientos = reserva("N_ASIENTOS")
			nif = reserva("NIF")
			cancelado = 0
			
			SentenciaSQL = "insert into RESERVA values ("&id_reserva & ",'" & apellidos & "','" & nombre & "'," & nif & "," & id_vuelo & "," & n_asientos & "," & cancelado & ")"
			Set rs = Conexion.Execute(SentenciaSQL)
			response.redirect("reservar2.asp?idvuelo=" & id_vuelo & "&idreserva=" &id_reserva)
		%>
     

	</body>
</html>