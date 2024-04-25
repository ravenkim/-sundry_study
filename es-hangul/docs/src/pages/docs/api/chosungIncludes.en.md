---
title: chosungIncludes
---

# chosungIncludes

Performs a search for matches in the initial consonants of a string.

```typescript
function chosungIncludes(
  // The string to be checked for matching initial consonants (e.g., '프론트엔드')
  x: string,
  // Initial consonant string (e.g., 'ㅍㄹㅌㅇㄷ')
  y: string
): boolean;
```

```typescript
chosungIncludes('프론트엔드', 'ㅍㄹㅌ'); // true
chosungIncludes('00프론트엔드', 'ㅍㄹㅌ'); // true
chosungIncludes('프론트엔드', 'ㅍㅌ'); // false
chosungIncludes('프론트엔드', '푸롴트'); // false
```
