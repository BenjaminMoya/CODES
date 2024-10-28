import { useState, useEffect } from "react";
import { Link, useNavigate} from "react-router-dom";
import Box from "@mui/material/Box";
import TextField from "@mui/material/TextField";
import Button from "@mui/material/Button";
import FormControl from "@mui/material/FormControl";
import DoneAllSharpIcon from '@mui/icons-material/DoneAllSharp';
import CalculateIcon from "@mui/icons-material/Calculate";
import CloseSharpIcon from '@mui/icons-material/CloseSharp';
import SavingsSharpIcon from '@mui/icons-material/SavingsSharp';
import Typography from "@mui/material/Typography";
import RemoveRedEyeSharpIcon from '@mui/icons-material/RemoveRedEyeSharp';
import CheckCircleOutlineSharpIcon from '@mui/icons-material/CheckCircleOutlineSharp';
import CancelSharpIcon from '@mui/icons-material/CancelSharp';
import userService from "../services/user.service";
import creditService from "../services/credit.service";
import Tooltip from "@mui/material/Tooltip";
import EventIcon from '@mui/icons-material/Event';
import AccountBalanceWalletIcon from '@mui/icons-material/AccountBalanceWallet';
import HistoryEduIcon from '@mui/icons-material/HistoryEdu';
import FormControlLabel from "@mui/material/FormControlLabel";
import Checkbox from "@mui/material/Checkbox"
import savingCapacityService from "../services/savingCapacity.service";
import fileService from "../services/file.service";

const CreditEvaluation = () => {

  const creditInit = JSON.parse(sessionStorage.getItem("toEvaluate"));
  const [creditId] = useState(creditInit.creditId);
  const [creditUserId] = useState(creditInit.creditUserId);
  const [creditPropertyAmount] = useState(creditInit.creditPropertyAmount);
  const [creditRequestedAmount] = useState(creditInit.creditRequestedAmount);
  const [creditTerm] = useState(creditInit.creditTerm);
  const [creditFirmDate,setCreditFirmDate] = useState(creditInit.creditFirmDate);
  const [creditType] = useState(creditInit.creditType);
  const [creditReason,setCreditReason] = useState("");
  const [interest, setInterest] = useState("");
  const [monthlyEntry, setMonthlyEntry] = useState("");
  const [monthlyDeposit, setMonthlyDeposit] = useState("");
  const [allDebts, setAllDebts] = useState("");
  const [topRetirement, setTopRetirement] = useState("");
  const [relationCI, setRelationCI] = useState("");
  const [relationDI, setRelationDI] = useState("");
  const [savingCapacity, setSavingCapacity] = useState("");
  const [age,setAge] = useState("");
  const [executive,setExecutive] = useState("");
  const [workSeniority,setWorkSeniority] = useState("");
  const [indepedent,setIndependent] = useState("");
  const [selectedFile1, setSelectedFile1] = useState(null);
  const today = new Date().toISOString().split('T')[0];
  const firmDate = new Date(creditFirmDate).toISOString().split('T')[0];
  const [options, setOptions] = useState({
    greatRetirement: false,
    periodicDeposits: false,
  });
  const navigate = useNavigate();
  
  const init = () => {

    userService
    .getById(sessionStorage.getItem("userId"))
    .then((response) => {
      console.log("Mostrando datos del usuario.", response.data);
      setAge(response.data.userAge);
      setExecutive(response.data.executive);
      setWorkSeniority(response.data.userWorkSeniority);
      setIndependent(response.data.userIndependent);
    })
    .catch((error) => {
      console.log(
        "Ha ocurrido un error al intentar obtener el estado de ejecutivo.",
        error
      );
    });
  };

  useEffect(() => {
    init();
  }, []);

  const handleFileChange1 = (event) => {
    setSelectedFile1(event.target.files[0]);
  };

  const handleDateChange = (e) => {
    const dateValue = e.target.value;
    
    const dateObject = new Date(dateValue);
    setCreditFirmDate(dateObject);
  };

  const ev1 = () => {
    if(creditType == 1){
      if(creditTerm <= 30){
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
            <Typography>Plazo:{creditTerm} años</Typography>
          </Box>
        )
      } else {
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
            <Typography>Plazo:{creditTerm} años</Typography>
          </Box>
        )
      }
    } else if(creditType == 2){
      if(creditTerm <= 20){
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
            <Typography>Plazo:{creditTerm} años</Typography>
          </Box>
        )
      } else {
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
            <Typography>Plazo:{creditTerm} años</Typography>
          </Box>
        )
      }
    } else if(creditType == 3){
      if(creditTerm <= 25){
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
            <Typography>Plazo:{creditTerm} años</Typography>
          </Box>
        )
      } else {
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
            <Typography>Plazo:{creditTerm} años</Typography>
          </Box>
        )
      }
    } else{
      if(creditTerm <= 15){
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
            <Typography>Plazo:{creditTerm} años</Typography>
          </Box>
        )
      } else {
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
            <Typography>Plazo:{creditTerm} años</Typography>
          </Box>
        )
      }
    }
  }

  const ev2 = () => {
    if(creditType == 1){
      if(creditRequestedAmount <= creditPropertyAmount*0.8){
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
            <Typography>Monto: ${creditRequestedAmount} (CLP)</Typography>
          </Box>
        )
      } else {
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
            <Typography>Monto: ${creditRequestedAmount} (CLP)</Typography>
          </Box>
        )
      }
    } else if(creditType == 2){
      if(creditRequestedAmount <= creditPropertyAmount*0.7){
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
            <Typography>Monto: ${creditRequestedAmount} (CLP)</Typography>
          </Box>
        )
      } else {
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
            <Typography>Monto: ${creditRequestedAmount} (CLP)</Typography>
          </Box>
        )
      }
    } else if(creditType == 3){
      if(creditRequestedAmount <= creditPropertyAmount*0.6){
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
            <Typography>Monto: ${creditRequestedAmount} (CLP)</Typography>
          </Box>
        )
      } else {
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
            <Typography>Monto: ${creditRequestedAmount} (CLP)</Typography>
          </Box>
        )
      }
    } else{
      if(creditRequestedAmount <= creditPropertyAmount*0.5){
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
            <Typography>Monto: ${creditRequestedAmount} (CLP)</Typography>
          </Box>
        )
      } else {
        return (
          <Box display="flex" alignItems="row" mb={1}>
            <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
            <Typography>Monto: ${creditRequestedAmount} (CLP)</Typography>
          </Box>
        )
      }
    }
  }

  const ev3 = () => {
    if(creditType == 1 && (interest < 3.5 || interest > 5)){
      return alert("El interes debe estar entre 3.5% y 5%");
    } else if(creditType == 2 && (interest < 4 || interest > 6)){
      return alert("El interes debe estar entre 4% y 6%");
    } else if(creditType == 3 && (interest < 5 || interest > 7)){
      return alert("El interes debe estar entre 5% y 7%");
    } else if(creditType == 4 && (interest < 4.5 || interest > 6)){
      return alert("El interes debe estar entre 4.5% y 6%");
    }

    creditService
    .relation1(creditRequestedAmount,interest,creditTerm,monthlyEntry)
    .then((response) => {
      console.log("Relacion CI: ", response.data);
      setRelationCI(response.data);
    })
    .catch((error) => {
      console.log(
        "Ha ocurrido un error al intentar obtener la relacion CI.",
        error
      );
    });
  };

  const ev4 = () => {
    creditService
    .simulation(creditRequestedAmount,interest,creditTerm)
    .then((response) => {
      console.log("Cuota mensual simulada: ", response.data);
      creditService
      .relation2(monthlyEntry,allDebts,response.data)
      .then((response) => {
        console.log("Relacion DI: ", response.data);
        setRelationDI(response.data);
      })
      .catch((error) => {
        console.log(
          "Ha ocurrido un error al intentar obtener la relacion DI.",
          error
        );
      });
    })
    .catch((error) => {
      console.log(
        "Ha ocurrido un error al intentar obtener la cuota mensual.",
        error
      );
    });
  };

  const ev5 = () => {
    if(age+creditTerm <= 75){
      return true;
    } else {
      return false;
    }
  };

  const handleChange = (event) => {
    setOptions({
      ...options,
      [event.target.name]: event.target.checked,
    });
  };

  const ev6 = () => {
    
    userService
    .zero(creditUserId)
    .then((response) => {
      console.log("Reinicio de condicion de ahorro: ", response.data);
      savingCapacityService
      .min(creditUserId,creditRequestedAmount)
      .then((response) => {
        console.log("Condicion de saldo minimo: ", response.data);
        savingCapacityService
        .history(creditUserId,options.greatRetirement)
        .then((response) => {
          console.log("Condicion de retiros significativos: ", response.data);
          savingCapacityService
          .periodic(creditUserId,monthlyDeposit,monthlyEntry,options.periodicDeposits)
          .then((response) => {
            console.log("Condicion de depositos periodicos: ", response.data);
            savingCapacityService
            .relation(creditUserId,creditRequestedAmount)
            .then((response) => {
              console.log("Condicion de relacion saldo/antiguedad: ", response.data);
              savingCapacityService
              .out(creditUserId,topRetirement)
              .then((response) => {
                console.log("Condicion de retiros maximos: ", response.data);
                userService
                .getById(creditUserId)
                .then((response) => {
                  console.log("Mostrando datos del usuario.", response.data);
                  setSavingCapacity(response.data.userSavingCapacity);
                })
                .catch((error) => {
                  console.log(
                    "Ha ocurrido un error al intentar obtener la capacidad de ahorro.",
                    error
                  );
                });
              })
              .catch((error) => {
                console.log(
                  "Ha ocurrido un error al intentar obtener la condicion de retiros maximos.",
                  error
                );
              });
            })
            .catch((error) => {
              console.log(
              "Ha ocurrido un error al intentar obtener la condicion de relacion saldo/antiguedad.",
              error
              );
            });
          })
          .catch((error) => {
            console.log(
              "Ha ocurrido un error al intentar obtener la condicion de depositos periodicos.",
              error
            );
          });
        })
        .catch((error) => {
          console.log(
            "Ha ocurrido un error al intentar obtener la condicion de retiros significativos.",
            error
          );
        });
      })
      .catch((error) => {
        console.log(
        "Ha ocurrido un error al intentar obtener la condicion de saldo minimo.",
        error
        );
      });
    })
    .catch((error) => {
      console.log("Ha ocurrido un error al intentar reiniciar la condicion de ahorro.", 
        error
      );
    });
  };

  const approve = (e) => {
    e.preventDefault();

    creditService
    .monthly(creditRequestedAmount,interest,creditTerm)
    .then((response) => {
      console.log("Cuota mensual: ", response.data);
      const credit = { creditId, creditUserId, creditPropertyAmount:creditInit.creditPropertyAmount, creditRequestedAmount, creditProposedAmount:response.data*12*creditTerm, creditPhase:4 ,creditTerm, creditFirmDate, creditType, creditReason};
      creditService
      .update(credit)
      .then((response) => {
        console.log("El credito ha sido aprobado.", response.data);
        navigate("/credit/list");
      })
      .catch((error) => {
        console.log(
          "Ha ocurrido un error al intentar aprobar el credito.",
          error
        );
      });
    })
    .catch((error) => {
      console.log("Ha ocurrido un error al intentar obtener la cuota mensual.", error);
    });
  };

  const reject = (e) => {
    e.preventDefault();
    
    const credit = { creditId, creditUserId, creditPropertyAmount, creditRequestedAmount, creditPhase:7 ,creditTerm, creditFirmDate, creditType, creditReason};
    creditService
    .update(credit)
    .then((response) => {
      console.log("El credito ha sido aprobado.", response.data);
      navigate("/credit/list");
    })
    .catch((error) => {
      console.log(
        "Ha ocurrido un error al intentar aprobar el credito.",
        error
      );
    });
  };

  const accept = (e) => {
    e.preventDefault();

    const credit = { creditId, creditUserId, creditPropertyAmount:creditInit.creditPropertyAmount, creditRequestedAmount, creditProposedAmount:creditInit.creditProposedAmount, creditPhase:4 ,creditTerm, creditFirmDate, creditType, creditReason:creditInit.creditReason};
    creditService
    .update(creditId)
    .then((response) => {
      console.log("El credito ha sido aprobado.", response.data);
      navigate("/user/credits");
    })
    .catch((error) => {
      console.log("Ha ocurrido un error al intentar aprobar el credito.", error);
    });
  };

  const cancel = (e) => {
    e.preventDefault();

    creditService
    .deleteCredit(creditId)
    .then((response) => {
      console.log("El credito ha sido cancelado.", response.data);
      navigate("/user/credits");
    })
    .catch((error) => {
      console.log("Ha ocurrido un error al intentar cancelar el credito.", error);
    });
  };

  const contract = (e) => {
    e.preventDefault();

    const credit = { creditId, creditUserId, creditPropertyAmount:creditInit.creditPropertyAmount, creditRequestedAmount, creditProposedAmount:creditInit.creditProposedAmount, creditPhase:6 ,creditTerm, creditFirmDate, creditType, creditReason:creditInit.creditReason};

    creditService
    .update(credit)
    .then((response) => {
      console.log("El credito ha sido aprobado.", response.data);
      fileService
      .upload(creditId,8,selectedFile1)
      .then((response) => {
        console.log("El contrato ha sido subido.", response.data);
        navigate("/user/credits");
      })
      .catch((error) => {
        console.log("Ha ocurrido un error al intentar subir el contrato.", error);
      });
      navigate("/credit/list");
    })
    .catch((error) => {
      console.log("Ha ocurrido un error al intentar aprobar el credito.", error);
    });
  };

  const finalAccept = (e) => {
    e.preventDefault();

    const credit = { creditId, creditUserId, creditPropertyAmount:creditInit.creditPropertyAmount, creditRequestedAmount, creditProposedAmount:creditInit.creditProposedAmount, creditPhase:9 ,creditTerm, creditFirmDate, creditType, creditReason:creditInit.creditReason};

    creditService
    .update(credit)
    .then((response) => {
      console.log("El credito ha sido aprobado.", response.data);
      navigate("/user/credits");
    })
    .catch((error) => {
      console.log("Ha ocurrido un error al intentar aprobar el credito.", error);
    });
  };

  const transfer = (e) => {
    e.preventDefault();

    const credit = { creditId, creditUserId, creditPropertyAmount:creditInit.creditPropertyAmount, creditRequestedAmount, creditProposedAmount:creditInit.creditProposedAmount, creditPhase:0 ,creditTerm, creditFirmDate, creditType, creditReason:creditInit.creditReason};
    userService
    .transfer(creditUserId,creditId)
    .then((response) => {
      console.log("El credito ha sido transferido.", response.data);
      creditService
      .update(credit)
      .then((response) => {
        console.log("El credito ha sido completado.", response.data);
        navigate("/credit/list");
      })
      .catch((error) => {
        console.log(
          "Ha ocurrido un error al intentar aprobar el credito.",
          error
        );
      });

    })
    .catch((error) => {
      console.log("Ha ocurrido un error al intentar transferir el credito.", error);
    });
  }

  if(executive && creditInit.creditPhase == 3){
    return (
      <div>
        <br />
        <div>
          <Box display="flex" alignItems="row" mb={1}>
            <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
            <Typography>Cumple con el requisito</Typography>
          </Box>
          <Box display="flex" alignItems="row" mb={1}>
            <RemoveRedEyeSharpIcon style={{ color: 'yellow', marginRight: 8 }} />
            <Typography>Requiere criterio del ejecutivo</Typography>
          </Box>
          <Box display="flex" alignItems="row">
            <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
            <Typography>No cumple con el requisito</Typography>
          </Box>
        </div>
        <Box
          display="flex"
          flexDirection="column"
          alignItems="center"
          justifyContent="center"
          component="form"
        >
          <h3> Datos del credito </h3>
          <form>
            <p> Usuario: {creditUserId} </p>
            <p> Fecha de solicitud: {creditFirmDate} </p>
            {creditType== 1 && (
              <p> Tipo de credito: Primera vivienda </p>
            )}
            {creditType== 2 && (
              <p> Tipo de credito: Segunda vivienda </p>
            )}
            {creditType== 3 && (
              <p> Tipo de credito: Propiedad comercial </p>
            )}
            {creditType== 4 && (
              <p> Tipo de credito: Remodelacion </p>
            )}
            <p> {ev1()} </p>
            <p> {ev2()} </p>
            { ev5() && (
              <Box display="flex" alignItems="row" mb={1}>
                <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
                <Typography>Termina de pagar antes de los 75 años de edad o menos </Typography>
              </Box>
            )}
            { !ev5() && (
              <Box display="flex" alignItems="row" mb={1}>
                <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
                <Typography>El pago del credito se extiende a mas de 75 años de edad</Typography>
              </Box>
            )}
            {relationCI && (
              <Box display="flex" alignItems="row" mb={1}>
                <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
                <Typography>Relacion CI menor a 35 %</Typography>
              </Box>
            )}
            {!relationCI && (
              <Box display="flex" alignItems="row" mb={1}>
                <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
                <Typography>Relacion CI mayor a 35%</Typography>
              </Box>
            )}
            { indepedent && (
              <Box display="flex" alignItems="row" mb={1}>
                <RemoveRedEyeSharpIcon style={{ color: 'yellow', marginRight: 8 }} />
                <Typography>Independiente: Requiere revisar ingresos de los ultimos 2 años</Typography>
              </Box>
            )}
            { !indepedent && workSeniority >= 1 && (
              <Box display="flex" alignItems="row" mb={1}>
                <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
                <Typography>Mas de 1 año de antiguedad laboral</Typography>
              </Box>
            )}
            { relationDI && (
              <Box display="flex" alignItems="row" mb={1}>
                <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
                <Typography>Relacion DI: Deudas menores que el 50% del ingreso mensual</Typography>
              </Box>
            )}
            { !relationDI && (
              <Box display="flex" alignItems="row" mb={1}>
                <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
                <Typography>Relacion DI: Deudas mayores que el 50% del ingreso mensual</Typography>
              </Box>
            )}
            { savingCapacity == 5 && (
              <Box display="flex" alignItems="row" mb={1}>
                <CheckCircleOutlineSharpIcon style={{ color: 'green', marginRight: 8 }} />
                <Typography>Capacidad de ahorro: Aprobada</Typography>
              </Box>
            )}
            { (savingCapacity == 3 || savingCapacity == 4) && (
              <Box display="flex" alignItems="row" mb={1}>
                <RemoveRedEyeSharpIcon style={{ color: 'yellow', marginRight: 8 }} />
                <Typography>Capacidad de ahorro: Moderada</Typography>
              </Box>
            )}
            { savingCapacity < 3  && (
              <Box display="flex" alignItems="row" mb={1}>
                <CancelSharpIcon style={{ color: 'red', marginRight: 8 }} />
                <Typography>Capacidad de ahorro: Rechazada</Typography>
              </Box>
            )} 
            <FormControl fullWidth>
            <TextField
              id="interest"
              label="Interes"
              value={interest}
              type="number"
              variant="standard"
              onChange={(e) => setInterest(e.target.value)}
              helperText="Porcentaje de interes (%)"
            />
            </FormControl>

            <h3> Caracteristicas del cliente  </h3>

            <FormControl fullWidth>
            <TextField
              id="monthlyEntry"
              label="Ingreso mensual"
              value={monthlyEntry}
              type="number"
              variant="standard"
              onChange={(e) => setMonthlyEntry(e.target.value)}
              helperText="Moneda local (CLP)"
            />
            </FormControl>

            <FormControl fullWidth>
            <TextField
              id="allDebts"
              label="Deudas totales al mes"
              value={allDebts}
              type="number"
              variant="standard"
              onChange={(e) => setAllDebts(e.target.value)}
              helperText="Moneda local (CLP)"
            />
            </FormControl>

            <FormControl fullWidth>
            <TextField
              id="monthlyDebts"
              label="Monto mensual depositado"  
              value={monthlyDeposit}
              type="number"
              variant="standard"
              onChange={(e) => setMonthlyDeposit(e.target.value)}
              helperText="Moneda local (CLP)"
            />
            </FormControl>

            <FormControl fullWidth>
            <TextField
              id="topRetirement"
              label="Monto maximo de retiro"  
              value={topRetirement}
              type="number"
              variant="standard"
              onChange={(e) => setTopRetirement(e.target.value)}
              helperText="Moneda local (CLP). En los ultimos 6 meses."
            />
            </FormControl>

            <div>
              <Box>
              <Tooltip title="El usuario hizo retiros de mas del 50% de su saldo o su saldo acumulado quedo en cero" arrow>
                <FormControlLabel
                  control={
                    <Checkbox
                      checked={options.greatRetirement}
                      onChange={handleChange}
                      name="greatRetirement"
                    />
                  }
                  label="Retiros significativos o saldo cero"
                />
              </Tooltip>
              </Box>
              <Box>
              <Tooltip title="El usuario realiza depositos en periodos regulares ya sean trimestrales o mensuales" arrow>
                <FormControlLabel
                  control={
                    <Checkbox
                      checked={options.periodicDeposits}
                      onChange={handleChange}
                      name="periodicDeposits"
                    />
                  }
                  label="Depositos periodicos"
                />
              </Tooltip>
              </Box>
            </div>

            <FormControl>
              <br />
              <Button
                variant="contained"
                color="info"
                onClick={(e) => ev3(e)}
                style={{ marginLeft: "0.5rem" }}
                startIcon={<CalculateIcon />}
              >
                Calcular CI
              </Button>
    
            </FormControl>

            <FormControl>
              <br />
              <Button
                variant="contained"
                color="info"
                onClick={(e) => ev4(e)}
                style={{ marginLeft: "0.5rem" }}
                startIcon={<CalculateIcon />}
              >
                Calcular DI
              </Button>
    
            </FormControl>
            <FormControl>
              <br />
              <Button
                variant="contained"
                color="info"
                onClick={(e) => ev6(e)}
                style={{ marginLeft: "0.5rem" }}
                startIcon={<SavingsSharpIcon />}
              >
                Evaluar capacidad de ahorro
              </Button>
    
            </FormControl>

            <h3> Razones crediticias </h3>

            <FormControl fullWidth>
            <TextField
              id="creditReason"
              label="Indicaciones"  
              value={creditReason}
              type="text"
              variant="standard"
              onChange={(e) => setCreditReason(e.target.value)}
              helperText="Si se planea rechazar el credito indique los motivo."
              multiline
              rows={4} 
            />
            </FormControl>
    
          </form>
          <br />
        </Box>
        <br />
        <Box>
          <form>
            <FormControl>
              <br />
              <Button
                variant="contained"
                color="info"
                onClick={(e) => approve(e)}
                style={{ marginLeft: "0.5rem" }}
                startIcon={<DoneAllSharpIcon />}
              >
                Aprobar
              </Button>
    
            </FormControl>
            <FormControl>
              <Button
                variant="contained"
                color="info"
                onClick={(e) => reject(e)}
                style={{ marginLeft: "0.5rem" }}
                startIcon={<CloseSharpIcon />}
              >
                Rechazar
              </Button>
            </FormControl>
            </form>
          </Box>
          <br />
            <Link to="/credit/list">Back to List</Link>
      </div>
    );

  } else if (executive && creditInit.creditPhase == 5){ 

    return (
      <Box
        display="flex"
        flexDirection="column"
        alignItems="center"
        justifyContent="center"
        component="form"
      >
        <h3> Datos del credito </h3>
        <form>
          <p> Monto solicitado: ${creditRequestedAmount} (CLP) </p>
          <p> Plazo: {creditTerm} </p>
          {creditType== 1 && (
            <p> Tipo de credito: Primera vivienda </p>
          )}
          {creditType== 2 && (
            <p> Tipo de credito: Segunda vivienda </p>
          )}
          {creditType== 3 && (
            <p> Tipo de credito: Propiedad comercial </p>
          )}
          {creditType== 4 && (
            <p> Tipo de credito: Remodelacion </p>
          )}
          
          <p>Etapa: Preparacion de documentacion </p>

          <FormControl fullWidth>
            <p>Programacion firma</p>
              <input
                type="date"
                min={today}
                onChange={handleDateChange}
              />
          </FormControl>
          <p>Fecha seleccionada: {creditFirmDate ? creditFirmDate.toDateString() : 'Ninguna'}</p>
  
          <br />
          <FormControl fullWidth style={{ marginTop: 16 }}>
          {selectedFile1 && (
              <p>Archivo seleccionado: {selectedFile1.name}</p>
          )}
            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
              alignItems="center"
            >
              Contrato crediticio 
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange1}
            />
            </Button>
          </FormControl>
          <FormControl>
            <br />
  
            <Button
              variant="contained"
              color="info"
              onClick={(e) => contract(e)}
              style={{ marginLeft: "0.5rem" }}
              startIcon={<HistoryEduIcon />}
            >
              Enviar contrato
            </Button>
          </FormControl>
        </form>
        <br />
        <Link to="/credit/list">Volver a la lista</Link>
      </Box>
    );

  } else if(!executive && creditInit.creditPhase == 6){ 

    return (
      <Box
        display="flex"
        flexDirection="column"
        alignItems="center"
        justifyContent="center"
        component="form"
      >
        <h3> Datos del credito </h3>
        <form>
          <p> Monto solicitado: ${creditRequestedAmount} (CLP) </p>
          <p> Plazo: {creditTerm} </p>
          <p> Etapa: Lista para desembolso </p>
          <p> Fecha de firma: {firmDate} </p>
  
          <br />
          
          <FormControl>
            <br />
  
            <Button
              variant="contained"
              color="info"
              onClick={(e) => finalAccept(e)}
              style={{ marginLeft: "0.5rem" }}
              startIcon={<EventIcon />}
            >
              Aceptar fecha
            </Button>
          </FormControl>
          <FormControl>
            <br />
  
            <Button
              variant="contained"
              color="info"
              onClick={(e) => cancel(e)}
              style={{ marginLeft: "0.5rem" }}
              startIcon={<CloseSharpIcon />}
            >
              Cancelar Solicitud
            </Button>
          </FormControl>
        </form>
        <br />
        <Link to="/credit/list">Volver a la lista</Link>
      </Box>
    );

  } else if(executive && creditInit.creditPhase == 9){ 

    return (
      <Box
        display="flex"
        flexDirection="column"
        alignItems="center"
        justifyContent="center"
        component="form"
      >
        <h3> Datos del credito </h3>
        <form>
          <p> Monto solicitado: ${creditRequestedAmount} (CLP) </p>
          <p> Plazo: {creditTerm} </p>
          <p> Etapa: En desembolso </p>
  
          <br />
          
          <FormControl>
            <br />
  
            <Button
              variant="contained"
              color="info"
              onClick={(e) => transfer(e)}
              style={{ marginLeft: "0.5rem" }}
              startIcon={<AccountBalanceWalletIcon />}
            >
              Transferir fondos
            </Button>
          </FormControl>
        </form>
        <br />
        <Link to="/credit/list">Volver a la lista</Link>
      </Box>
    );
  } else if(!executive && creditInit.creditPhase == 0){ 

    return (
      <Box
        display="flex"
        flexDirection="column"
        alignItems="center"
        justifyContent="center"
        component="form"
      >
        <h3> Datos del credito </h3>
        <form>
          <p> Monto solicitado: ${creditRequestedAmount} (CLP) </p>
          <p> Plazo: {creditTerm} años</p>
          <p> Etapa: Transferida </p>
  
        </form>
        <br />
        <Link to="/user/credits">Volver a la lista</Link>
      </Box>
    ); 
  } else {

    return (
      <Box
        display="flex"
        flexDirection="column"
        alignItems="center"
        justifyContent="center"
        component="form"
      >
        <h3> Datos del credito </h3>
        <form>
          <p> Monto solicitado: ${creditRequestedAmount} (CLP) </p>
          <p> Plazo: {creditTerm} </p>
          {creditType== 1 && (
            <p> Tipo de credito: Primera vivienda </p>
          )}
          {creditType== 2 && (
            <p> Tipo de credito: Segunda vivienda </p>
          )}
          {creditType== 3 && (
            <p> Tipo de credito: Propiedad comercial </p>
          )}
          {creditType== 4 && (
            <p> Tipo de credito: Remodelacion </p>
          )}
          {creditInit.creditPhase == 3 && (
            <p>Etapa: En evaluacion </p>
          )}
          {creditInit.creditPhase == 4 && (
            <div>
              <p>Etapa: Pre-aprobada </p>
              <p>Propuesta de monto final: ${creditInit.creditProposedAmount} (CLP)</p>
              <p>Propuesta de cuota mensual: ${creditInit.creditProposedAmount/(12*creditTerm)} (CLP)</p>
              <FormControl>
                <br />
  
                <Button
                  variant="contained"
                  color="info"
                  onClick={(e) => accept(e)}
                  style={{ marginLeft: "0.5rem" }}
                  startIcon={<DoneAllSharpIcon />}
                >
                  Aceptar propuesta
                </Button>
              </FormControl>
            </div>
          )}
          {creditInit.creditPhase == 5 && (
            <p>Etapa: Preparacion de documentacion </p>
          )}
          {creditInit.creditPhase == 6 && (
            <p>Etapa: Lista para desembolso</p>
          )}
          {creditInit.creditPhase == 7 && (
            <p>Etapa: Rechazada </p>
          )}
          {creditInit.creditPhase == 9 && (
            <p>Etapa: En desembolso </p>
          )}
          <br />
          <FormControl>
            <br />
  
            <Button
              variant="contained"
              color="info"
              onClick={(e) => cancel(e)}
              style={{ marginLeft: "0.5rem" }}
              startIcon={<CloseSharpIcon />}
            >
              Cancelar Solicitud
            </Button>
          </FormControl>
        </form>
        <br />
        <Link to="/credit/list">Volver a la lista</Link>
      </Box>
    );
  }
};

export default CreditEvaluation;