import axios from "axios";

const backEndServer = impor.meta.env.VITE_BACKEND_SERVER;
const backEndPort = impor.meta.env.VITE_BACKEND_PORT;

console.log(backEndServer)
console.log(backEndPort)

export default axios.create({
    baseURL: `http://${backEndServer}:${backEndPort}`,
    headers: {
        'Content-Type' : 'application/json'
    }
});