#!/usr/bin/env bash

cleos push action eosio.token create '["eosio.token","1000000.0000 SYS"]' -p eosio.token@active
cleos push action eosio.token issue '{"to":"tester","quantity":"500.0000 SYS","memo":""}' -p eosio.token
cleos push action eosio.token issue '{"to":"rider","quantity":"500.0000 SYS","memo":""}' -p eosio.token
cleos push action eosio.token issue '{"to":"seller","quantity":"500.0000 SYS","memo":""}' -p eosio.token

cleos set account permission rideos active '{"threshold": 1,"keys": [{"key": "EOS8BCgapgYA2L4LJfCzekzeSr3rzgSTUXRXwNi8bNRoz31D14en9","weight": 1}],"accounts": [{"permission":{"actor":"rideos","permission":"eosio.code"},"weight":1}]}' owner -p rideos
cleos set account permission tester active '{"threshold": 1,"keys": [{"key": "EOS78RuuHNgtmDv9jwAzhxZ9LmC6F295snyQ9eUDQ5YtVHJ1udE6p","weight": 1}],"accounts": [{"permission":{"actor":"rideos","permission":"active"},"weight":1}]}' owner -p tester@active
cleos set account permission rider active '{"threshold": 1,"keys": [{"key": "EOS8LoJJUU3dhiFyJ5HmsMiAuNLGc6HMkxF4Etx6pxLRG7FU89x6X","weight": 1}],"accounts": [{"permission":{"actor":"rideos","permission":"active"},"weight":1}]}' owner -p rider@active
cleos set account permission seller active '{"threshold": 1,"keys": [{"key": "EOS5yd9aufDv7MqMquGcQdD6Bfmv6umqSuh9ru3kheDBqbi6vtJ58","weight": 1}],"accounts": [{"permission":{"actor":"rideos","permission":"active"},"weight":1}]}' owner -p seller@active
sleep 1

cleos push action rideos add '["tester","tester"]' -p tester
cleos push action rideos add '["rider","rid"]' -p rider
cleos push action rideos add '["seller","sel"]' -p seller
sleep 1

cleos get table rideos rideos user