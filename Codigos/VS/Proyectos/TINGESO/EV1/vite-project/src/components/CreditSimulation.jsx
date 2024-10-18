import { useState } from "react";
import { useNavigate } from "react-router-dom";
import CalculateIcon from "@mui/icons-material/Calculate";
import Box from "@mui/material/Box";
import TextField from "@mui/material/TextField";
import Button from "@mui/material/Button";
import FormControl from "@mui/material/FormControl";
import MenuItem from "@mui/material/MenuItem";
import creditService from "../services/credit.service";

const CreditSimulation = () => {
  const [amount, setAmount] = useState("");
  const [interest, setInterest] = useState("");
  const [year, setYear] = useState("");

  const navigate = useNavigate();

  const calculateSimulation = (e) => {
    e.preventDefault();
    console.log("Solicitar calcular simulacion.", amount,"-",interest,"-",year);
    creditService
      .simulation(amount, interest, year)
      .then((response) => {
        console.log("Cuota mensual simulada: ", response.data);
      })
      .catch((error) => {
        console.log(
          "Ha ocurrido un error al intentar calcular la simulacion del credito.",
          error
        );
      });
    console.log("Fin calculo de la simulacion.");
  };

  return (
    <Box
      display="flex"
      flexDirection="column"
      alignItems="center"
      justifyContent="center"
      component="form"
    > 
      <div>
        <h3> Simulacion de credito hipotecario</h3>
      </div>
      <form>
        
        <FormControl fullWidth>
          <TextField
            id="amount"
            label="Monto"
            value={amount}
            variant="standard"
            onChange={(e) => setAmount(e.target.value)}
            helperText="Moneda local (CLP)"
          />
        </FormControl>

        <FormControl fullWidth>
          <TextField
            id="interest"
            label="Interes anual"
            value={interest}
            variant="standard"
            onChange={(e) => setInterest(e.target.value)}
          />
        </FormControl>

        <FormControl fullWidth>
          <TextField
            id="year"
            label="Plazo"
            value={year}
            variant="standard"
            onChange={(e) => setYear(e.target.value)}
            helperText="Formato anual. Ejemplo: 20, 30, 40"
          />
        </FormControl>

      {/*
        <FormControl fullWidth>
          <TextField
            id="month"
            label="Month"
            value={month}
            select
            variant="standard"
            defaultValue="1"
            onChange={(e) => setMonth(e.target.value)}
            style={{ width: "25%" }}
          >
            <MenuItem value={1}>Enero</MenuItem>
            <MenuItem value={2}>Febrero</MenuItem>
            <MenuItem value={3}>Marzo</MenuItem>
            <MenuItem value={4}>Abril</MenuItem>
            <MenuItem value={5}>Mayo</MenuItem>
            <MenuItem value={6}>Junio</MenuItem>
            <MenuItem value={7}>Julio</MenuItem>
            <MenuItem value={8}>Agosto</MenuItem>
            <MenuItem value={9}>Septiembre</MenuItem>
            <MenuItem value={10}>Octubre</MenuItem>
            <MenuItem value={11}>Noviembre</MenuItem>
            <MenuItem value={12}>Diciembre</MenuItem>
          </TextField>
        </FormControl>
      */}

        <FormControl>
          <br />
          <Button
            variant="contained"
            color="info"
            onClick={(e) => calculateSimulation(e)}
            style={{ marginLeft: "0.5rem" }}
            startIcon={<CalculateIcon />}
          >
            Simular credito
          </Button>
        </FormControl>
      </form>
    </Box>
  );
};

export default CreditSimulation;
