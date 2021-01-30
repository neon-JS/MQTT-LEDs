import { Environment } from "../models/Environment";

export const environment : Environment = {
  production: true,
  mqtt: {
    host: '',
    username: '',
    password: ''
  },
  ledDevices: []
};
