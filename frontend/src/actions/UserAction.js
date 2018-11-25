import { ActionTypes } from 'const';

class UserAction {

  static setUser({ account, username, balance }) {
    return {
      type: ActionTypes.SET_USER,
      account,      // EOS name
      username, // Users pseudo
      balance,// Users balance
    }
  }
}

export default UserAction;