import React from 'react';

export const ThemeContext = React.createContext({
  theme: 'dark',
  toggleTheme: () => { },
});


export default function ThemeContextProvider({ children }) {
  const [theme, setTheme] = React.useState('dark');


  const toggleTheme = () => {
    setTheme((prevTheme) => {
      return prevTheme === 'dark' ? 'light' : 'dark';
    });
  };

  let ctxValue = { theme: theme, toggleTheme: toggleTheme }

  return (
    <ThemeContext.Provider value={ctxValue}>
      {children}
    </ThemeContext.Provider>
  );
}
