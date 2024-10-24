import { useEffect, useState} from "react";
import { Link, useNavigate, useParams} from "react-router-dom";
import CreditScoreSharpIcon from '@mui/icons-material/CreditScoreSharp';
import Table from "@mui/material/Table";
import TableBody from "@mui/material/TableBody";
import TableCell, { tableCellClasses } from "@mui/material/TableCell";
import TableContainer from "@mui/material/TableContainer";
import TableHead from "@mui/material/TableHead";
import TableRow from "@mui/material/TableRow";
import Paper from "@mui/material/Paper";
import Button from "@mui/material/Button";
import creditService from "../services/credit.service";


const UserCredits = () => {
    const [credits, setCredits] = useState([]);
    const [userId]= sessionStorage.getItem("userId");
    const navigate = useNavigate();

    const init = () => {
        console.log(userId);
        creditService
        .getAll(userId)
        .then((response) => {
            console.log("Mostrando listado de creditos del usuario.", response.data);
            setCredits(response.data);
        })
        .catch((error) => {
            console.log(
                "Se ha producido un error al intentar mostrar listado creditos del usuario.",
                error
            );
        });
    };

    useEffect(() => {
        init();
    }, []);

    const goEvaluation = (data) => {
        sessionStorage.setItem("toEvaluate",JSON.stringify(data));
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
          {credits.map((credit) => (
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
                  startIcon={<CreditScoreSharpIcon />}
                >
                  Ver estado
                </Button>
              </TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
    </TableContainer>
  );
};

export default UserCredits;
