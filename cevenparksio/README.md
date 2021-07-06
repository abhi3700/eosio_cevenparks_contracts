# CEVEN.Parks

## ACTION
* `depostfund`
<!-- * `withdrawfund` -->
* `signup`
* `login`
* `addparkdata`
* `delparktree`
* `enterpark`

## TABLE
* `profile`
	- username
	- email_id
	- password_hash
	- is_logged_in
* `userentry` (scope: park_id)
	- username
	- is_checked_in (0: outside, 1: inside)
* `parkinfo` (scope: park_id)
	- tree_id
	- long
	- lat
	- species
	- latin_species
	- year_planted
	- diameter_canopy
	- dbh
	- height
	- biomass
* `fund` (scope: username)
  - username
	- deposit_qty

## Compile
```console
$ eosio-cpp cevenparksio.cpp -o cevenparksio.wasm
Warning, action <signup> does not have a ricardian contract
Warning, action <logininout> does not have a ricardian contract
Warning, action <deluser> does not have a ricardian contract
Warning, action <addparkdata> does not have a ricardian contract
Warning, action <editparkdata> does not have a ricardian contract
Warning, action <delparktree> does not have a ricardian contract
Warning, action <entrexitpark> does not have a ricardian contract
```

## Deploy
* deploy contract
```console
$ cleost set contract cevenparksio ./
Reading WASM from /mnt/f/Coding/github_repos/snihack2021/contracts/cevenparksio/cevenparksio.wasm...
Publishing contract...
executed transaction: 5ceec83ba99129f5d08ebfda56e28a2ff5e56bca1bdc29e4847fe3b0f86acdd7  24848 bytes  2207 us
#         eosio <= eosio::setcode               {"account":"cevenparksio","vmtype":0,"vmversion":0,"code":"0061736d0100000001c1022e60000060037f7f7f0...
#         eosio <= eosio::setabi                {"account":"cevenparksio","abi":"0e656f73696f3a3a6162692f312e32000d0b6164647061726b64617461000907747...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Adding eosio.code to permissions (for inline actions)
```console
$ cleost set account permission cevenparksio active --add-code
executed transaction: e76b11a8bc3477798b706242e37fb673c88b76b39c2fbe47937aaa43b2caf39a  184 bytes  152 us
#         eosio <= eosio::updateauth            {"account":"cevenparksio","permission":"active","parent":"owner","auth":{"threshold":1,"keys":[{"key...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Testing
### ACTION - signup
* user signup
```console
$ cleost push action cevenparksio signup '["cpusr1111111", "abhi3700@gmail.com", "48357a7f102bb38d88d1aa5b7f887f70c0309f31a78cd57bf30e34e4a4017a76"]' -p cevenparksio@active
executed transaction: a3ca63bb0d0652f16b4ce3b5e908f3742c97c1417bf20466824b3afb8c3201df  152 bytes  261 us
#  cevenparksio <= cevenparksio::signup         {"username":"cpusr1111111","email_id":"abhi3700@gmail.com","password_hash":"48357a7f102bb38d88d1aa5b...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* view table
```console
$ cleost get table cevenparksio cevenparksio profile --show-payer --lower cpusr1111111 --upper cpusr1111111
{
  "rows": [{
      "data": {
        "username": "cpusr1111111",
        "email_id": "abhi3700@gmail.com",
        "password_hash": "48357a7f102bb38d88d1aa5b7f887f70c0309f31a78cd57bf30e34e4a4017a76",
        "is_logged_in": 0
      },
      "payer": "cevenparksio"
    }
  ],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```
* user signup again
```console
$ cleost -u http://jungle3.cryptolions.io:80 push action cevenparksio signup '["cpusr1111111", "abhi3700@gmail.com", "48357a7f102bb38d88d1aa5b7f887f70c0309f31a78cd57bf30e34e4a4017a76"]' -p cevenparksio@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: username already exists. So, no signup needed.
pending console output:
```

### ACTION - login
* user login
```console
$ cleost push action cevenparksio logininout '["cpusr1111111", "48357a7f102bb38d88d1aa5b7f887f70c0309f31a78cd57bf30e34e4a4017a76", "1"]' -p cevenparksio@active
executed transaction: 301a54a47e4cda1e57bddda5fe9a94714ad975f892639f84b89571e92ceff171  136 bytes  243 us
#  cevenparksio <= cevenparksio::logininout     {"username":"cpusr1111111","password_hash":"48357a7f102bb38d88d1aa5b7f887f70c0309f31a78cd57bf30e34e4...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* view table
```console
$ cleost get table cevenparksio cevenparksio profile --show-payer --lower cpusr1111111 --upper cpusr1111111
{
  "rows": [{
      "data": {
        "username": "cpusr1111111",
        "email_id": "abhi3700@gmail.com",
        "password_hash": "48357a7f102bb38d88d1aa5b7f887f70c0309f31a78cd57bf30e34e4a4017a76",
        "is_logged_in": 1
      },
      "payer": "cevenparksio"
    }
  ],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```
* user login again & gets error as the user is already logged in
```console
$ cleost push action cevenparksio logininout '["cpusr1111111", "48357a7f102bb38d88d1aa5b7f887f70c0309f31a78cd57bf30e34e4a4017a76", "1"]' -p cevenparksio@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: the parsed user login status is same as stored one.
pending console output:
```

### ACTION - logout
* user logout
```console
$ cleost push action cevenparksio logout '["cpusr1111111"]' -p cevenparksio@active
executed transaction: 264cb2ce627f56585d7590932a6c20edc04eb73ce8b98ffa4c2197b7fe6ced3a  136 bytes  276 us
#  cevenparksio <= cevenparksio::logout     {"username":"cpusr1111111"
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

### ACTION - addparkdata
* added park data via python [script](../data/uppark2.py)
* view the data of park with id - `17000000001625384306` [here](https://jungle3.bloks.io/account/cevenparksio?loadContract=true&tab=Tables&table=parkinfo&account=cevenparksio&scope=17000000001625384306&limit=100)

### ACTION - delparktree
* deleted the park tree
```console
$ cleost push action cevenparksio delparktree '['17000000001625384306', '4']' -p cevenparksio@active
executed transaction: bdc25ce7c5596ce6066f1783c35dcdc9dba305892cfca5da12de8fdd949d3b52  112 bytes  267 us
#  cevenparksio <= cevenparksio::delparktree    {"park_id":"17000000001625384306","tree_id":4}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

### ACTION - entrexitpark
* a person enters a park with id - `17000000001625384306`
```console
$ cleost push action cevenparksio entrexitpark '["cpusr1111111", "17000000001625384306", "1"]' -p cevenparksio@active
executed transaction: 5b6d2f8fdf1ff5e4c0ef84a352f291c9a2a4f8cec322200e669eab94b54ba286  112 bytes  331 us
#  cevenparksio <= cevenparksio::entrexitpark   {"username":"cpusr1111111","park_id":"17000000001625384306","is_checked_in":1}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* a person exits a park with id - `17000000001625384306`
```console
$ cleost push action cevenparksio entrexitpark '["cpusr1111111", "17000000001625384306", "0"]' -p cevenparksio@active
executed transaction: 7ca9ac3a5f1704fa6b21a7c60013f1f49d56dcb702baa19bd7625844395d28d9  112 bytes  491 us
#  cevenparksio <= cevenparksio::entrexitpark   {"username":"cpusr1111111","park_id":"17000000001625384306","is_checked_in":0}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

### Action - `deposit` (on_notify action)
#### EOS
* `cpusr1111111` transfer some quantity (in EOS) to contract account
  - show the cevenparksio accounts balance of `cpusr1111111`
```console
$ cleost get table cevenparksio cevenparksio fund --show-payer --lower cpusr1111111 --upper cpusr1111111
{
  "rows": [],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```
  - show the eosio.token balance (EOS) of `cpusr1111111`
```console
$ cleost get table eosio.token cpusr1111111 accounts --show-payer
{
  "rows": [{
      "data": {
        "balance": "100.0000 EOS"
      },
      "payer": "junglefaucet"
    },{
      "data": {
        "balance": "100.0000 JUNGLE"
      },
      "payer": "junglefaucet"
    }
  ],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```
  - transfer
```console
$ cleost push action eosio.token transfer '["cpusr1111111", "cevenparksio", "1.0000 EOS", "deposit"]' -p cpusr1111111@active
executed transaction: 9584cd58c4aadfcca981123a63ebd79cdab548ae2f20ce599739570e722fbcb4  136 bytes  344 us
#   eosio.token <= eosio.token::transfer        {"from":"cpusr1111111","to":"cevenparksio","quantity":"1.0000 EOS","memo":"deposit"}
#  cpusr1111111 <= eosio.token::transfer        {"from":"cpusr1111111","to":"cevenparksio","quantity":"1.0000 EOS","memo":"deposit"}
#  cevenparksio <= eosio.token::transfer        {"from":"cpusr1111111","to":"cevenparksio","quantity":"1.0000 EOS","memo":"deposit"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
  - show the cevenparksio accounts balance of `cpusr1111111`
```console
$ cleost get table cevenparksio cevenparksio fund --show-payer --lower cpusr1111111 --upper cpusr1111111
{
  "rows": [{
      "data": {
        "username": "cpusr1111111",
        "deposit_qty": [{
            "key": {
              "sym": "4,EOS",
              "contract": "eosio.token"
            },
            "value": 10000
          }
        ]
      },
      "payer": "cevenparksio"
    }
  ],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```
  - show the eosio.token (EOS) balance of `cpusr1111111`
```console
$ cleost get table eosio.token cpusr1111111 accounts --show-payer
{
  "rows": [{
      "data": {
        "balance": "99.0000 EOS"
      },
      "payer": "cpusr1111111"
    },{
      "data": {
        "balance": "100.0000 JUNGLE"
      },
      "payer": "junglefaucet"
    }
  ],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```


## References