import httpCommon from "../http-common";

const upload = (id,type,file) => {
    return httpCommon.post(`/api/file/upload/${id}`,{params:{type,file}});
}

const download = (id,type) => {
    return httpCommon.get(`/api/file/download/${id}`,{params:{type}});
}

export default { upload, download };