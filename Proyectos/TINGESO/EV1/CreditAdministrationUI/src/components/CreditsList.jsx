import { useEffect, useState } from "react";
import { Link, useNavigate } from "react-router-dom";
import CreditScoreSharpIcon from '@mui/icons-material/CreditScoreSharp';
import Table from "@mui/material/Table";
import TableBody from "@mui/material/TableBody";
import TableCell, { tableCellClasses } from "@mui/material/TableCell";
import TableContainer from "@mui/material/TableContainer";
import TableHead from "@mui/material/TableHead";
import TableRow from "@mui/material/TableRow";
import Paper from "@mui/material/Paper";
import Button from "@mui/material/Button";
import AppRegistrationSharpIcon from '@mui/icons-material/AppRegistrationSharp';
import creditService from "../services/credit.service";


const CreditsList = () => {
  const [credit1, setCredit1] = useState([]);
  const [credit2, setCredit2] = useState([]);
  const [credit3, setCredit3] = useState([]);

  const navigate = useNavigate();

  const init = () => {
    creditService
    .getPhase(3)
    .then((response) => {
      setCredit1(response.data);
    })
    .catch((error) => {
      console.log(
        "Se ha producido un error al intentar mostrar listado creditos por evaluar.",
        error
      );
    });
    
    creditService
    .getPhase(5)
    .then((response) => {
      setCredit2(response.data);
    })
    .catch((error) => {
      console.log(
      "Se ha producido un error al intentar mostrar listado creditos por evaluar.",
       error
      );
    });

    creditService
    .getPhase(9)
    .then((response) => {
      setCredit3(response.data);
    })
    .catch((error) => {
      console.log(
      "Se ha producido un error al intentar mostrar listado creditos por evaluar.",
       error
      );
    });
  };

  useEffect(() => {
    init();
  }, []);

  const goEvaluation = (credit) => {
    sessionStorage.setItem("toEvaluate", JSON.stringify(credit));
    navigate("/credit/evaluation");
  };

  return (
     <TableContainer component={Paper}>
        <br />

        <br /> <br />
        <Table sx={{ minWidth: 650 }} size="small" aria-label="a dense table">
            <TableHead>
            <TableRow>
                <TableCell align="left" sx={{ fontWeight: "bold" }}>
                Id 
                </TableCell>
                <TableCell align="left" sx={{ fontWeight: "bold" }}>
                Tipo de credito
                </TableCell>
                <TableCell align="right" sx={{ fontWeight: "bold" }}>
                Monto solicitado
                </TableCell>
                <TableCell align="right" sx={{ fontWeight: "bold" }}>
                Plazo 
                </TableCell>
                <TableCell align="right" sx={{ fontWeight: "bold" }}>
                Fase de evaluacion
                </TableCell>
            </TableRow>
            </TableHead>
        <TableBody>
          {credit1.map((credit) => (
            <TableRow
              key={credit.creditId}
              sx={{ "&:last-child td, &:last-child th": { border: 0 } }}
            >
                <TableCell align="left">{credit.creditId}</TableCell>
                {credit.creditType== 1 && (
                    <TableCell align="left">Primera vivienda
                    </TableCell>
                )}
                {credit.creditType == 2 && (
                <TableCell align="left">Segunda vivienda
                </TableCell>
                )}
                {credit.creditType == 3 && (
                <TableCell align="left">Propiedad comercial
                </TableCell>
                )}
                {credit.creditType == 4 && (
                <TableCell align="left">Remodelacion
                </TableCell>
                )}
                <TableCell align="right">{credit.creditRequestedAmount}</TableCell>
                <TableCell align="center">{credit.creditTerm}</TableCell>
                <TableCell align="center">{credit.creditPhase}</TableCell>
                <TableCell>
                <Button
                  variant="contained"
                  color="info"
                  size="small"
                  onClick={() => goEvaluation(credit)}
                  style={{ marginLeft: "0.5rem" }}
                  startIcon={<AppRegistrationSharpIcon />}
                >
                  Evaluar
                </Button>
              </TableCell>
            </TableRow>
          ))}
          {credit2.map((credit) => (
            <TableRow
              key={credit.creditId}
              sx={{ "&:last-child td, &:last-child th": { border: 0 } }}
            >
                <TableCell align="left">{credit.creditId}</TableCell>
                {credit.creditType== 1 && (
                    <TableCell align="left">Primera vivienda
                    </TableCell>
                )}
                {credit.creditType == 2 && (
                <TableCell align="left">Segunda vivienda
                </TableCell>
                )}
                {credit.creditType == 3 && (
                <TableCell align="left">Propiedad comercial
                </TableCell>
                )}
                {credit.creditType == 4 && (
                <TableCell align="left">Remodelacion
                </TableCell>
                )}
                <TableCell align="right">{credit.creditRequestedAmount}</TableCell>
                <TableCell align="center">{credit.creditTerm}</TableCell>
                <TableCell align="center">{credit.creditPhase}</TableCell>
                <TableCell>
                <Button
                  variant="contained"
                  color="info"
                  size="small"
                  onClick={() => goEvaluation(credit)}
                  style={{ marginLeft: "0.5rem" }}
                  startIcon={<AppRegistrationSharpIcon />}
                >
                  Evaluar
                </Button>
              </TableCell>
            </TableRow>
          ))}
          {credit3.map((credit) => (
            <TableRow
              key={credit.creditId}
              sx={{ "&:last-child td, &:last-child th": { border: 0 } }}
            >
                <TableCell align="left">{credit.creditId}</TableCell>
                {credit.creditType== 1 && (
                    <TableCell align="left">Primera vivienda
                    </TableCell>
                )}
                {credit.creditType == 2 && (
                <TableCell align="left">Segunda vivienda
                </TableCell>
                )}
                {credit.creditType == 3 && (
                <TableCell align="left">Propiedad comercial
                </TableCell>
                )}
                {credit.creditType == 4 && (
                <TableCell align="left">Remodelacion
                </TableCell>
                )}
                <TableCell align="right">{credit.creditRequestedAmount}</TableCell>
                <TableCell align="center">{credit.creditTerm}</TableCell>
                <TableCell align="center">{credit.creditPhase}</TableCell>
                <TableCell>
                <Button
                  variant="contained"
                  color="info"
                  size="small"
                  onClick={() => goEvaluation(credit)}
                  style={{ marginLeft: "0.5rem" }}
                  startIcon={<AppRegistrationSharpIcon />}
                >
                  Evaluar
                </Button>
              </TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
    </TableContainer>
  );
};

export default CreditsList;
