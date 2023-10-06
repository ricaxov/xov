# Hash Table
## A simple, but hopefully efectfull, class about Hash Tables - by xov 😎

### Concepts

#### Division Hashing:
- Just a basic hashing technique, where you make the index of the current value equal to the $Hash(key)$.

#### Double Hashing:
- Another basic thing in hashing, where you hash two keys for a single value, to make sure it will not cause collisions, like so:

```py
index = {key1, key2}
```

#### Chaining Hashing:
- Create a linked list in an index of our Hash Table to bypass the problems with collisions.

#### Multiplying Hashing:
- We use prime number multiplications to find the key where our current value will stay at.

#### Hashing function:
![HASH-FUNCTION](https://cybersecurityglossary.com/wp-content/uploads/2019/07/Hash-function.jpg)

#### A simple, but nice, way to calculate Hashing:

**Let's assume that S is the string we want to hash and it has size N:**

$Hash(S) = S[0] + S[1] * P + S[2] * P ^ 2 + ... + S[K] * P ^ K % M$

In these case, K is equal to N - 1, P and M are positive numbers, usually prime. 

#### Simple implementation:
```c++
int Hash(string key) {
  int H = 0;
  for(int i = 0; i < (int)key.size(); i++) {
    H = (H * 3 + key[i]) % 10;
  }
  return H;
}
```

#### My Hash implementation:
```c++
const int mod1 = 1000015553, mod2 = 1000028537;
const int base1 = 37, base2 = 31;
struct HashedString {
  int n;
  string s;
  vector<int> hsh1, pwr1, hsh2, pwr2;
 
  HashedString() : n(0) {}
  HashedString(string s) : n(sz(s)), s(s), hsh1(n), pwr1(n), hsh2(n), pwr2(n) {	
    pwr1[0] = pwr2[0] = 1;
    for (int i = 1; i < n; i++) {
      pwr1[i] = (base1 * pwr1[i - 1]) % mod1;
      pwr2[i] = (base2 * pwr2[i - 1]) % mod2;
    }
    hsh1[0] = hsh2[0] = s[0];
    for(int i = 1; i < n; i++) {
      hsh1[i] = (hsh1[i - 1] * base1 + (int)(s[i])) % mod1;
      hsh2[i] = (hsh2[i - 1] * base2 + (int)(s[i])) % mod2;
    }
  }
  int hash(int i, int j) {
    if (i == 0) return (hsh1[j] << 30) ^ (hsh2[j]);
    int ret1 = ((hsh1[j] - (hsh1[i - 1] * pwr1[j - i + 1])) % mod1 + mod1) % mod1;
    int ret2 = ((hsh2[j] - (hsh2[i - 1] * pwr2[j - i + 1])) % mod2 + mod2) % mod2;
    return (ret1 << 30) ^ (ret2);
  }
};
```

---

### Questions

#### 1st question
**Basically we will have a hypothetical scenario where we have two heroes:**

```py
1st = "Batman"
2nd = "Superman"

Hash("Batman") = 1234
Hash("Superman") = 1234
```

**How do we fix this problem?**

We just iterate over our Hash Table and use a index which has not been used before or we can just use linked lists.

**How do we get rid of this problem?**

We have lots of ways of getting rid of our hashing collision without having to use another data structure, but the easiest one is probably double hashing, which consists in just hashing twice.

#### 2nd question

**Insert:**

```py
Insert "Elder Wand", "Manoel's Wand", "Luis's Wand"
```

Since the "Elder Wand" and "Manoel's Wand" collided on the 0th index we create a linked list to make room for both of them:

```py
Hash_Table[0] = {"Elder Wand", "Manoel's Wand"}
Hash_Table[1] = {"Luis's Wand"}
Hash_Table[2] = {}
```

**Search:**

```py
Search "Elder Wand", "Manoel's Wand", "Ricardo's Wand"
```

We will find both the "Elder Wand" and "Manoel's Wand", but not "Ricardo's Wand":

```py
"Elder Wand", "Manoel's Wand" were found on Hash_Table, at the 0th position
"Ricardo's Wand" does not exist on Hash_Table
```

**Delete:**

```py
Delete "Elder Wand", "Manoel's Wand", "Ricardo's Wand"
```

We will delete both the "Elder Wand" and "Manoel's Wand", but not "Ricardo's Wand":

```py
"Elder Wand", "Manoel's Wand" were deleted from Hash_Table, at the 0th position
"Ricardo's Wand" does not exist on Hash_Table
```

#### 3rd question

**Absence of thought implementation:**
```c++
class Hash_Table {
  map<pair<int, int>, int> TABLE;
  void insert(pair<int, int> key, int value) {
    TABLE[key] = value;
  }
  bool search(pair<int, int> key) {
    if(TABLE.find(key) == end(TABLE)) return 0;
    return 1;
  }
  void erase(int key) {
    if(TABLE.find(key) == end(TABLE)) return;
    TABLE.erase(TABLE.find(key));
  }
};
```
> Please don't do something dumb like this 😅

I'd choose double hashing, since it's a lot easier.

#### 4th question

The hashing function can be used to ensure integrity of data, because it will store, access and modify it.

```py
Hash("Batmobile") = 12873
Hash("Batarang") = 31293
Hash("Batmilk") = 42069
```

As we can see it's literally impossible to confuse our hashed items.

#### 5th question

**Let's assume that:**

```py
Hash("Luke") = Hash("Yoda")
```

This would cause a failure in the data integrity, but this problem could easily be solved using Double Hashing, Chaining Hashing and possibly some other methods.

Since Double Hashing is probably the easiest is the one i will choose again:

```py
Hash("Luke") = {key1, key2}
Hash("Yoda") = {key1, key3}
```

Now the hashed values will surelly be different.

#### 6th question

We should define a load factor, which is commonly define as 70%, to solve our problem eficiently.

#### 7th question

We could just use Double Hashing with Chaining Hashing which would probably work just fine, because it would minimize our possible collisions, and in case it does happen it would fix our problem anyway, so it seems fine to me.

**Simple Implementation:**
```c++
struct Hash {
  int N;
  pair<int, int> H;
  Hash() : N(0) {};
  Hash(string s) {
    N = (int)s.size();
    int ff = 0, ss = 0;
    for(int i = 0; i < N; i++) {
      ff = (ff * 3 + s[i]) % N;
      ss = (ss * 5 + s[i]) % N;
    }
    H = {ff, ss};
  }
};
```

#### 8th question

**Double Hashing:**

```py
Hash("Dungeons") = {1, 4}
Hash("Dragons") = {2, 3}

Hash_Table[0] = "Dungeons"
Hash_Table[1] = "Dragons"
```

**Chaining Hashing:**

```py
Hash("Dungeons") = 2
Hash("Dragons") = 1

Hash_Table[0] = "Dragons"
Hash_Table[1] = "Dungeons"
```

As we can see using different methods might result in different configurations on our Hash Table.

#### 9th question

**Colision:**
```py
Hash("Spok") = Hash("Kirk")
```
**Solution:**
```py
Hash("Spok") = (Hash("Spok") + 2 * 2) % N
Hash("Kirk") = (Hash("Kirk") + 3 * 3) % N
```

Using this tecnique we will probably not have the same slots occupied at the same time, like we did before.

#### 10th question

**Supose that:**

Our Hash Table has a capacity of only three slots which are currently being used:

```py
Hash_Table[0] = {"Bilbo"}
Hash_Table[1] = {"Frodo"}
Hash_Table[2] = {"Gandalf"}
```

Now we try to insert a new character into our Hash Table:

```py
Insert "Celeborn"
```

**What will happen?**

We will need to increase the size of our Table, since otherwise it will not fit, just like so:

```py
Expand Hash_Table
```

**Results:**

- Tough code implementation
- Relocation costs
- Possible collisions
