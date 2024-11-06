import httpCommon from '../http-common';

const getAll = () => {
  return httpCommon.get('/api/user/get');
}

const getById = (id) => {
  return httpCommon.get(`/api/user/getById/${id}`);
}

const getByRut = (rut) => {
  return httpCommon.get(`/api/user/getByRut/${rut}`);
}

const getByEmail = (email) => {
  return httpCommon.get(`/api/user/getByEmail/${email}`);
}

const create = (data) => {
  return httpCommon.post('/api/user/save', data);
}

const login = (data) => {
  return httpCommon.post('/api/user/login', data);
}

const update = (data) => {
    return httpCommon.put('/api/user/update', data);
}

const remove = (id) => {
    return httpCommon.delete(`/api/user/delete/${id}`);
}

const zero = (id) => {
    return httpCommon.post(`/api/user/zero/${id}`);
}

const transfer = (userId,creditId) => {
    return httpCommon.post("/api/user/transfer",{ userId, creditId});
}

export default { getAll, getById, getByRut, getByEmail, create, login, update, remove, zero, transfer };