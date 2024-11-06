import { useState, useEffect } from "react";
import { useParams, useNavigate } from "react-router-dom";
import Box from "@mui/material/Box";
import TextField from "@mui/material/TextField";
import Button from "@mui/material/Button";
import FormControl from "@mui/material/FormControl";
import MenuItem from "@mui/material/MenuItem";
import AccountBalance from '@mui/icons-material/AccountBalance';
import creditService from "../services/credit.service";
import fileService from "../services/file.service";

const CreditApplication = () => {

  const [creditUserId, setCreditUserId] = useState("0");
  const [creditPropertyAmount, setCreditPropertyAmount] = useState("");
  const [creditRequestedAmount, setCreditRequestedAmount] = useState("");
  const [creditPhase] = useState("3");
  const [creditType, setCrediType] = useState("1");
  const [creditTerm, setCreditTerm] = useState("");
  const [creditFinishDate, setCreditFinishDate] = useState("");
  const [latePayment] = useState("false");
  const [maxAmount,setMaxAmount] = useState("");
  const [selectedFile1, setSelectedFile1] = useState(null);
  const [selectedFile2, setSelectedFile2] = useState(null);
  const [selectedFile3, setSelectedFile3] = useState(null);
  const [selectedFile4, setSelectedFile4] = useState(null);
  const navigate = useNavigate();

  const handleFileChange1 = (event) => {
    setSelectedFile1(event.target.files[0]);
  };

  const handleFileChange2 = (event) => {
    setSelectedFile2(event.target.files[0]);
  };

  const handleFileChange3 = (event) => {
    setSelectedFile3(event.target.files[0]);
  };

  const handleFileChange4 = (event) => {
    setSelectedFile4(event.target.files[0]);
  };

  const makeDate = (years) => {
    const date = new Date();
    date.setFullYear(date.getFullYear() + years);
    return date;
  };

  const updateUserId = () => {
    setCreditUserId(JSON.parse(sessionStorage.getItem("userId")));
  };

  useEffect(() => {
    updateUserId();
  }, []);

  const saveCredit = (e) => {
    e.preventDefault();

    if(creditRequestedAmount=="" || creditPropertyAmount=="" || creditTerm==""){
      alert("Debe completar todos los campos.");
      return;
    }

    if(isNaN(creditRequestedAmount) || isNaN(creditPropertyAmount) || isNaN(creditTerm)){
      alert("Los campos monto, precio de la propiedad y plazo deben ser numeros enteros.");
      return;
    }

    if(creditRequestedAmount%1 != 0 || creditPropertyAmount%1 != 0 || creditTerm%1 != 0){
      alert("Los campos monto, precio de la propiedad y plazo deben ser numeros enteros.");
      return;
    }
    
    if(creditType == 1 && selectedFile1 && selectedFile2 && selectedFile3){
      setMaxAmount(creditRequestedAmount*0,8);
    } else if(creditType == 2 && selectedFile1 && selectedFile2 && selectedFile3 && selectedFile4){
      setMaxAmount(creditRequestedAmount*0,7);
    } else if(creditType == 3 && selectedFile1 && selectedFile2 && selectedFile3 && selectedFile4){
      setMaxAmount(creditRequestedAmount*0,6);
    } else if(creditType == 4 && selectedFile1 && selectedFile2 && selectedFile3){
      setMaxAmount(creditRequestedAmount*0,5);
    } else {
      alert("Faltan archivos por adjuntar.");
      return;
    }

    setCreditFinishDate(makeDate(creditTerm));
    const credit = { creditUserId, creditPropertyAmount, creditRequestedAmount, creditPhase, creditTerm, creditFinishDate, creditType, latePayment, maxAmount };
    console.log("Datos del credito:", credit);
    if (creditUserId) {
      creditService
      .create(credit)
      .then((response) => {
        console.log("El credito ha sido solicitado.", response.data);
        const creditId = response.data.creditId;
        if(creditType == 1){
          fileService
          .upload(creditId,1,selectedFile1)
          .then((response) => {
            console.log("Archivo 1 subido: ", response.data);
            fileService
            .upload(creditId,2,selectedFile2)
            .then((response) => {
              console.log("Archivo 2 subido: ", response.data);
              fileService
              .upload(creditId,3,selectedFile3)
              .then((response) => {
                console.log("Archivo 3 subido: ", response.data);
                navigate("/user/credits");
              })
              .catch((error) => {
                console.log(
                  "Ha ocurrido un error al subir el archivo 3.",
                  error
                );
              });
            })
            .catch((error) => {
              console.log(
                "Ha ocurrido un error al subir el archivo 2.",
                error
              );
            });
          })
          .catch((error) => {
            console.log(
              "Ha ocurrido un error al subir el archivo 1.",
              error
            );
          });
        } else if (creditType == 2){
          fileService
          .upload(creditId,1,selectedFile1)
          .then((response) => {
            console.log("Archivo 1 subido: ", response.data);
            fileService
            .upload(creditId,2,selectedFile2)
            .then((response) => {
              console.log("Archivo 2 subido: ", response.data);
              fileService
              .upload(creditId,4,selectedFile4)
              .then((response) => {
                console.log("Archivo 3 subido: ", response.data);
                fileService
                .upload(creditId,3,selectedFile3)
                .then((response) => {
                  console.log("Archivo 3 subido: ", response.data);
                  navigate("/user/credits");
                })
                .catch((error) => {
                  console.log(
                    "Ha ocurrido un error al subir el archivo 3.",
                    error
                  );
                });  
              })
              .catch((error) => {
                console.log(
                  "Ha ocurrido un error al subir el archivo 3.",
                  error
                );
              });
            })
            .catch((error) => {
              console.log(
                "Ha ocurrido un error al subir el archivo 2.",
                error
              );
            });
          })
          .catch((error) => {
            console.log(
              "Ha ocurrido un error al subir el archivo 1.",
              error
            );
          });
        } else if(creditType == 3){
          fileService
          .upload(creditId,5,selectedFile1)
          .then((response) => {
            console.log("Archivo 1 subido: ", response.data);
            fileService
            .upload(creditId,1,selectedFile2)
            .then((response) => {
              console.log("Archivo 2 subido: ", response.data);
              fileService
              .upload(creditId,2,selectedFile3)
              .then((response) => {
                console.log("Archivo 3 subido: ", response.data);
                fileService
                .upload(creditId,6,selectedFile3)
                .then((response) => {
                  console.log("Archivo 3 subido: ", response.data);
                  navigate("/user/credits");
                })
                .catch((error) => {
                  console.log(
                    "Ha ocurrido un error al subir el archivo 3.",
                    error
                  );
                });  
              })
              .catch((error) => {
                console.log(
                  "Ha ocurrido un error al subir el archivo 3.",
                  error
                );
              });
            })
            .catch((error) => {
              console.log(
                "Ha ocurrido un error al subir el archivo 2.",
                error
              );
            });
          })
          .catch((error) => {
            console.log(
              "Ha ocurrido un error al subir el archivo 1.",
              error
            );
          });
        } else if(creditType == 4){
          fileService
          .upload(creditId,1,selectedFile1)
          .then((response) => {
            console.log("Archivo 1 subido: ", response.data);
            fileService
            .upload(creditId,7,selectedFile2)
            .then((response) => {
              console.log("Archivo 2 subido: ", response.data);
              fileService
              .upload(creditId,8,selectedFile3)
              .then((response) => {
                console.log("Archivo 3 subido: ", response.data);
                navigate("/user/credits");
              })
              .catch((error) => {
                console.log(
                  "Ha ocurrido un error al subir el archivo 3.",
                  error
                );
              });
            })
            .catch((error) => {
              console.log(
                "Ha ocurrido un error al subir el archivo 2.",
                error
              );
            });
          })
          .catch((error) => {
            console.log(
              "Ha ocurrido un error al subir el archivo 1.",
              error
            );
          });
        }
      })
      .catch((error) => {
        console.log(
          "Ha ocurrido un error al solicitar el credito.",
          error
        );
      });
    } else {
      alert("Debe iniciar sesion para solicitar un credito.");
    }
  };

  const renderButtons = () => {
    switch (creditType) {
      case "1":
        return (
          <FormControl fullWidth style={{ marginTop: 16 }}>
            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Comprobante de ingresos
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange1}
            />
            </Button>
            {selectedFile1 && (
              <p>Primer archivo seleccionado: {selectedFile1.name}</p>
            )}

            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Certificado de avalúo
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange2}
            />
            </Button>
            {selectedFile2 && (
              <p>Segundo archivo seleccionado: {selectedFile2.name}</p>
            )}

            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Historial crediticio
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange3}
            />
            </Button>
            {selectedFile3 && (
              <p>Tercer archivo seleccionado: {selectedFile3.name}</p>
            )}
          </FormControl>
        );
      case "2":
        return (
          <FormControl fullWidth style={{ marginTop: 16 }}>
            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Comprobante de ingresos
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange1}
            />
            </Button>
            {selectedFile1 && (
              <p>Primer archivo seleccionado: {selectedFile1.name}</p>
            )}

            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Certificado de avalúo
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange2}
            />
            </Button>
            {selectedFile2 && (
              <p>Segundo archivo seleccionado: {selectedFile2.name}</p>
            )}

            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Escritura de la primera vivienda
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange3}
            />
            </Button>
            {selectedFile3 && (
              <p>Tercer archivo seleccionado: {selectedFile3.name}</p>
            )}

            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Historial crediticio
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange4}
            />
            </Button>
            {selectedFile4 && (
              <p>Cuarto archivo seleccionado: {selectedFile4.name}</p>
            )}
          </FormControl>
        );
      case "3":
        return (
          <FormControl fullWidth style={{ marginTop: 16 }}>
            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Estado financiero del negocio
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange1}
            />
            </Button>
            {selectedFile1 && (
              <p>Primer archivo seleccionado: {selectedFile1.name}</p>
            )}

            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Comprobante de ingresos
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange2}
            />
            </Button>
            {selectedFile2 && (
              <p>Segundo archivo seleccionado: {selectedFile2.name}</p>
            )}

            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Certificado de avalúo
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange3}
            />
            </Button>
            {selectedFile3 && (
              <p>Tercer archivo seleccionado: {selectedFile3.name}</p>
            )}

            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Plan de negocios
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange4}
            />
            </Button>
            {selectedFile4 && (
              <p>Cuarto archivo seleccionado: {selectedFile4.name}</p>
            )}
          </FormControl>
        );
      case "4":
        return (
          <FormControl fullWidth style={{ marginTop: 16 }}>
            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Comprobante de ingresos
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange1}
            />
            </Button>
            {selectedFile1 && (
              <p>Primer archivo seleccionado: {selectedFile1.name}</p>
            )}

            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Presupuesto de remodelacion
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange2}
            />
            </Button>
            {selectedFile2 && (
              <p>Segundo archivo seleccionado: {selectedFile2.name}</p>
            )}

            <Button 
              variant="contained" 
              component="label"
              size="small"
              style={{ margin: '8px 0', width: '200px' }} 
            >
              Certificado de avalúo actualizado
            <input
              type="file"
              accept=".pdf"
              hidden
              onChange={handleFileChange3}
            />
            </Button>
            {selectedFile3 && (
              <p>Tercer archivo seleccionado: {selectedFile3.name}</p>
            )}
          </FormControl>
        );
      default:
        return null;
    }
  };

  return (
    <Box
      display="flex"
      flexDirection="column"
      alignItems="center"
      justifyContent="center"
      component="form"
    >
      <h3> Solicitud crediticia </h3>
      <form>
        <FormControl fullWidth>
          <TextField
            id="amount"
            label="Precio de la propiedad"
            value={creditPropertyAmount}
            variant="standard"
            onChange={(e) => setCreditPropertyAmount(e.target.value)}
            helperText="Moneda local (CLP)"
          />
        </FormControl>

        <FormControl fullWidth>
          <TextField
            id="amount"
            label="Monto"
            value={creditRequestedAmount}
            variant="standard"
            onChange={(e) => setCreditRequestedAmount(e.target.value)}
            helperText="Moneda local (CLP)"
          />
        </FormControl>

        <FormControl fullWidth>
          <TextField
            id="type"
            label="Tipo de credtio hipotecario"
            value={creditType}
            select
            variant="standard"
            defaultValue="1"
            onChange={(e) => setCrediType(e.target.value)}
            style={{ width: "25%" }}
          >
            <MenuItem value={"1"}>Primera vivienda</MenuItem>
            <MenuItem value={"2"}>Segunda vivienda</MenuItem>
            <MenuItem value={"3"}>Propiedades comerciales</MenuItem>
            <MenuItem value={"4"}>Remodelacion</MenuItem>
          </TextField>
        </FormControl>

        <FormControl fullWidth>
          <TextField
            id="year"
            label="Plazo"
            value={creditTerm}
            variant="standard"
            onChange={(e) => setCreditTerm(e.target.value)}
            helperText="Formato anual. Ejemplo: 20, 30, 40"
          />
        </FormControl>
        
        <div style={{ marginTop: 16 }}>
          {renderButtons()}
        </div>
        <FormControl>
          <br />
          <Button
            variant="contained"
            color="info"
            onClick={(e) => saveCredit(e)}
            style={{ marginLeft: "0.5rem" }}
            startIcon={<AccountBalance />}
          >
            Solicitar credito
          </Button>
        </FormControl>
      </form>
    </Box>
  );
};

export default CreditApplication;