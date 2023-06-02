class LoggedOutState : public AuthenticationState {
public:
    void login() override;
    void logout() override;
};

class LoggingInState : public AuthenticationState {
public:
    void login() override;
    void logout() override;
};

class LoggedInState : public AuthenticationState {
public:
    void login() override;
    void logout() override;
};

void LoggedOutState::login() {
    // attempt to log in
    if (login_successful) {
        // transition to the LoggedInState
        authentication_system_->set_state(new LoggedInState(authentication_system_));
    } else {
        // transition to the LoggingInState
        authentication_system_->set_state(new LoggingInState(authentication_system_));
    }
}

void LoggingInState::login() {
    // attempt to log in
    if (login_successful) {
        // transition to the LoggedInState
        authentication_system_->set_state(new LoggedInState(authentication_system_));
    } else {
        // transition back to the LoggedOutState
        authentication_system_->set_state(new LoggedOutState(authentication_system_));
    }
}

void LoggedInState::logout() {
    // log out
    // transition to the LoggedOutState
    authentication_system_->set_state(new LoggedOutState(authentication_system_));
}

class AuthenticationSystem {
public:
    AuthenticationSystem() : state_(new LoggedOutState(this)) {}

    void set_state(AuthenticationState* state) {
        delete state_;
        state_ = state;
    }

    void login() {
        state_->login();
    }

    void logout() {
        state_->logout();
    }

private:
    AuthenticationState* state_;
};

int main(){
	
	AuthenticationSystem auth_system;
	auth_system.login();
	
	return 0;
}