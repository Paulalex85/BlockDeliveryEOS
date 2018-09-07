#include "Users.hpp"

namespace rideEOS {

    EOSIO_ABI(Users, (add)(update)(getuser)(deposit)(withdraw));

    void Users::add(account_name account, string& username) {
        require_auth(account);
        userIndex users(_self, _self);

        auto iterator = users.find(account);
        eosio_assert(iterator == users.end(), "Address for account already exists");

        users.emplace(account, [&](auto& user) {
            user.account_name = account;
            user.username = username;
        });
    }

    void Users::update(account_name account, string& username) {
        require_auth(account);
        userIndex users(_self, _self);

        auto iterator = users.find(account);
        eosio_assert(iterator != users.end(), "Address for account not found");

        users.modify(iterator, account, [&](auto& user) {
            user.username = username;
        });
    }

    void Users::getuser(const account_name account) {
        userIndex users(_self, _self);

        auto iterator = users.find(account);
        eosio_assert(iterator != users.end(), "Address for account not found");

        auto currentUser = users.get(account);
        print("Username: ", currentUser.username.c_str());
    }

    void Users::deposit(const account_name account, const asset& quantity ) {
        eosio_assert( quantity.is_valid(), "invalid quantity" );
        eosio_assert( quantity.amount > 0, "must deposit positive quantity" );

        userIndex users(_self, _self);

        auto iterator = users.find(account);
        eosio_assert(iterator != users.end(), "Address for account not found");

        action(
            permission_level{ account, N(active) },
            N(eosio.token),
            N(transfer),
            std::make_tuple(account, _self, quantity, std::string(""))
        ).send();

        users.modify(iterator, account, [&](auto& user) {
            user.balance += quantity;
        });
    }

    void Users::withdraw( const account_name account, const asset& quantity ) {
        require_auth(account);

        eosio_assert( quantity.is_valid(), "invalid quantity" );
        eosio_assert( quantity.amount > 0, "must withdraw positive quantity" );

        userIndex users(_self, _self);

        auto iterator = users.find(account);
        eosio_assert(iterator != users.end(), "Address for account not found");

        users.modify(iterator, account, [&](auto& user) {
            eosio_assert( user.balance >= quantity, "insufficient balance" );
            user.balance -= quantity;
        });

        action(
            permission_level{ _self, N(active) },
            N(eosio.token), N(transfer),
            std::make_tuple(_self, account, quantity, std::string(""))
        ).send();
    }
}