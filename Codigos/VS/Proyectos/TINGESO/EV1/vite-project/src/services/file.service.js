import httpCommon from "../http-common";

const create = (data) => {
    return httpCommon.post("/api/file/create", data);
}

const get = (id,type) => {
    return httpCommon.get("/api/file/get",{params:{id,type}});
}

const upload = (file) => {
    return httpCommon.post("/api/file/upload",{params:{file}});
}

const download = (filename) => {
    return httpCommon.get(`/api/file/download`,{params:{filename}});
}

export default { create, get ,upload, download };