---
title: disassembleHangul
---

# disassembleHangul

Completely separates a Hangul string into its individual characters by initial consonants, medial vowels, and final consonants, creating a single string.

For detailed examples, see below.

```typescript
function disassembleHangul(
  // The Korean string to be disassembled
  str: string
): string;
```

## Examples

```tsx
disassembleHangul('값'); // 'ㄱㅏㅂㅅ'
disassembleHangul('값이 비싸다'); // 'ㄱㅏㅂㅅㅇㅣ ㅂㅣㅆㅏㄷㅏ'
disassembleHangul('ㅘ'); // 'ㅗㅏ'
disassembleHangul('ㄵ'); // 'ㄴㅈ'
```
